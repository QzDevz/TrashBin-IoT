/*
 * 🤖 ESP32 Smart Trashcan - IoT Enhanced Version
 * Professional IoT-enabled smart trashcan with web interface
 *
 * Features:
 * - WiFi connectivity and web server
 * - REST API endpoints for external integration
 * - Real-time web dashboard
 * - mDNS support (smarttrashcan.local)
 * - Remote lid control via web interface
 * - Usage statistics and analytics
 * - Professional mobile app integration ready
 *
 * Hardware Requirements:
 * - ESP32 Development Board
 * - SG90 Servo Motor
 * - HC-SR04 Ultrasonic Sensors (x2)
 * - Red LED (5mm) + 220Ω resistor
 * - 5V Power supply
 *
 * Network Requirements:
 * - WiFi SSID and password
 * - Port 80 for web server
 *
 * Version: 1.0.0
 * Last Updated: December 2024
 */

#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Servo.h>
#include <ArduinoJson.h>

// ========== NETWORK CONFIGURATION ==========
const char* ssid = "YOUR_WIFI_SSID";        // Replace with your WiFi SSID
const char* password = "YOUR_WIFI_PASSWORD"; // Replace with your WiFi password

// ========== PIN DEFINITIONS ==========
#define SERVO_PIN           18    // Servo motor control pin
#define LED_PIN             19    // Status LED pin (PWM)
#define TRIG_PIN_HAND       5     // Hand detection trigger pin
#define ECHO_PIN_HAND       17    // Hand detection echo pin
#define TRIG_PIN_TRASH      16    // Trash level trigger pin
#define ECHO_PIN_TRASH      4     // Trash level echo pin

// ========== CONFIGURATION ==========
#define HAND_DETECTION_THRESHOLD  15  // Distance in cm for hand detection
#define LID_OPEN_ANGLE           90   // Servo angle for open position
#define LID_CLOSE_ANGLE          0    // Servo angle for closed position
#define AUTO_CLOSE_DELAY         5000 // Auto-close delay in milliseconds
#define SENSOR_READ_INTERVAL     100  // Sensor reading interval in milliseconds
#define LED_UPDATE_INTERVAL      50   // LED update interval in milliseconds
#define WEB_SERVER_PORT          80   // Web server port

// ========== GLOBAL OBJECTS ==========
Servo lidServo;
WebServer server(WEB_SERVER_PORT);

// ========== GLOBAL VARIABLES ==========
struct DeviceStatus {
  bool lidOpen = false;
  int trashLevel = 0;
  float handDistance = 0;
  float trashDistance = 0;
  unsigned long lastMotion = 0;
  unsigned long totalOpens = 0;
  unsigned long uptime = 0;
  String firmwareVersion = "1.0.0";
} deviceStatus;

// Timing variables
unsigned long lastSensorRead = 0;
unsigned long lastLedUpdate = 0;
unsigned long lidOpenTime = 0;

// LED variables
int ledBrightness = 0;

// ========== SETUP FUNCTION ==========
void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("🤖 ESP32 Smart Trashcan - IoT Enhanced Version");
  Serial.println("==============================================");

  // Initialize servo
  lidServo.attach(SERVO_PIN);
  lidServo.write(LID_CLOSE_ANGLE);
  Serial.println("✅ Servo initialized");

  // Initialize ultrasonic sensors
  pinMode(TRIG_PIN_HAND, OUTPUT);
  pinMode(ECHO_PIN_HAND, INPUT);
  pinMode(TRIG_PIN_TRASH, OUTPUT);
  pinMode(ECHO_PIN_TRASH, INPUT);
  Serial.println("✅ Ultrasonic sensors initialized");

  // Initialize LED
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, 0);
  Serial.println("✅ LED initialized");

  // Connect to WiFi
  connectToWiFi();

  // Setup mDNS
  if (MDNS.begin("smarttrashcan")) {
    Serial.println("✅ mDNS responder started: http://smarttrashcan.local");
  }

  // Setup web server routes
  setupWebServer();

  // Start web server
  server.begin();
  Serial.println("✅ Web server started on port " + String(WEB_SERVER_PORT));

  // Initial sensor reading
  readSensors();

  Serial.println("✅ System ready!");
  Serial.println("📱 Access web interface at: http://smarttrashcan.local");
  Serial.println("📱 Or IP address: " + WiFi.localIP().toString());
  Serial.println("");
}

// ========== MAIN LOOP ==========
void loop() {
  unsigned long currentTime = millis();

  // Handle web server
  server.handleClient();

  // Read sensors at specified interval
  if (currentTime - lastSensorRead >= SENSOR_READ_INTERVAL) {
    readSensors();
    lastSensorRead = currentTime;
  }

  // Update LED at specified interval
  if (currentTime - lastLedUpdate >= LED_UPDATE_INTERVAL) {
    updateLED();
    lastLedUpdate = currentTime;
  }

  // Handle lid operation
  handleLidOperation();

  // Update uptime
  deviceStatus.uptime = currentTime / 1000; // Convert to seconds

  // Small delay for stability
  delay(10);
}

// ========== WIFI FUNCTIONS ==========
void connectToWiFi() {
  Serial.print("🔗 Connecting to WiFi");
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi connected!");
    Serial.print("📍 IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("🌐 Signal Strength: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  } else {
    Serial.println("\n❌ Failed to connect to WiFi");
    Serial.println("📡 Continuing in offline mode");
  }
}

// ========== SENSOR FUNCTIONS ==========
void readSensors() {
  // Read hand detection sensor
  deviceStatus.handDistance = readUltrasonicDistance(TRIG_PIN_HAND, ECHO_PIN_HAND);

  // Read trash level sensor
  deviceStatus.trashDistance = readUltrasonicDistance(TRIG_PIN_TRASH, ECHO_PIN_TRASH);

  // Calculate trash level (assuming 20cm max depth)
  deviceStatus.trashLevel = constrain(map(deviceStatus.trashDistance, 2, 20, 100, 0), 0, 100);

  // Update motion timestamp if hand detected
  if (deviceStatus.handDistance > 0 && deviceStatus.handDistance <= HAND_DETECTION_THRESHOLD) {
    deviceStatus.lastMotion = millis();
  }
}

float readUltrasonicDistance(int trigPin, int echoPin) {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo pulse
  unsigned long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout

  // Calculate distance in cm
  float distance = duration * 0.034 / 2;

  return distance;
}

// ========== LID CONTROL FUNCTIONS ==========
void handleLidOperation() {
  unsigned long currentTime = millis();

  // Check if hand is detected
  if (deviceStatus.handDistance > 0 && deviceStatus.handDistance <= HAND_DETECTION_THRESHOLD) {
    if (!deviceStatus.lidOpen) {
      openLid();
      Serial.println("✋ Hand detected - Opening lid");
    }
    lidOpenTime = currentTime; // Reset auto-close timer
  }

  // Auto-close lid after delay
  if (deviceStatus.lidOpen && (currentTime - lidOpenTime >= AUTO_CLOSE_DELAY)) {
    closeLid();
    Serial.println("⏰ Auto-closing lid");
  }
}

void openLid() {
  lidServo.write(LID_OPEN_ANGLE);
  deviceStatus.lidOpen = true;
  deviceStatus.totalOpens++;
  Serial.print("✅ Lid opened at angle: ");
  Serial.println(LID_OPEN_ANGLE);
}

void closeLid() {
  lidServo.write(LID_CLOSE_ANGLE);
  deviceStatus.lidOpen = false;
  Serial.println("✅ Lid closed");
}

// ========== LED CONTROL FUNCTIONS ==========
void updateLED() {
  // Calculate LED brightness based on trash level
  if (deviceStatus.trashLevel < 30) {
    // Empty - dim green (simulated with low brightness)
    ledBrightness = 50;
  } else if (deviceStatus.trashLevel < 70) {
    // Half full - medium orange (simulated with medium brightness)
    ledBrightness = 150;
  } else {
    // Full - bright red (simulated with high brightness)
    ledBrightness = 255;
  }

  // Apply brightness with PWM
  analogWrite(LED_PIN, ledBrightness);
}

// ========== WEB SERVER FUNCTIONS ==========
void setupWebServer() {
  // Root page - Dashboard
  server.on("/", HTTP_GET, handleRoot);

  // API endpoints
  server.on("/api/status", HTTP_GET, handleStatus);
  server.on("/api/sensor-data", HTTP_GET, handleSensorData);
  server.on("/api/open-lid", HTTP_POST, handleOpenLid);
  server.on("/api/close-lid", HTTP_POST, handleCloseLid);
  server.on("/api/reset", HTTP_POST, handleReset);

  // Static files
  server.on("/style.css", HTTP_GET, handleCSS);
  server.on("/script.js", HTTP_GET, handleJS);

  // 404 handler
  server.onNotFound(handleNotFound);
}

void handleRoot() {
  String html = R"html(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart Trashcan Dashboard</title>
    <link rel="stylesheet" href="/style.css">
</head>
<body>
    <div class="container">
        <h1>🤖 Smart Trashcan Dashboard</h1>

        <div class="status-grid">
            <div class="status-card">
                <h3>Lid Status</h3>
                <div class="status-indicator" id="lid-status"></div>
                <button onclick="toggleLid()" id="lid-button">Toggle Lid</button>
            </div>

            <div class="status-card">
                <h3>Trash Level</h3>
                <div class="level-bar">
                    <div class="level-fill" id="trash-level"></div>
                </div>
                <span id="trash-percentage">0%</span>
            </div>

            <div class="status-card">
                <h3>Hand Detection</h3>
                <div class="status-indicator" id="hand-status"></div>
                <span id="hand-distance">0 cm</span>
            </div>
        </div>

        <div class="info-grid">
            <div class="info-card">
                <h3>Device Information</h3>
                <p><strong>IP Address:</strong> <span id="ip-address">)html" + WiFi.localIP().toString() + R"html(</span></p>
                <p><strong>Firmware:</strong> <span id="firmware">)html" + deviceStatus.firmwareVersion + R"html(</span></p>
                <p><strong>Uptime:</strong> <span id="uptime">0s</span></p>
            </div>

            <div class="info-card">
                <h3>Usage Statistics</h3>
                <p><strong>Total Opens:</strong> <span id="total-opens">0</span></p>
                <p><strong>Last Motion:</strong> <span id="last-motion">Never</span></p>
                <p><strong>WiFi Signal:</strong> <span id="wifi-signal">0 dBm</span></p>
            </div>
        </div>
    </div>

    <script src="/script.js"></script>
</body>
</html>)html";

  server.send(200, "text/html", html);
}

void handleStatus() {
  StaticJsonDocument<512> doc;

  doc["lidOpen"] = deviceStatus.lidOpen;
  doc["trashLevel"] = deviceStatus.trashLevel;
  doc["handDistance"] = deviceStatus.handDistance;
  doc["totalOpens"] = deviceStatus.totalOpens;
  doc["uptime"] = deviceStatus.uptime;
  doc["firmware"] = deviceStatus.firmwareVersion;
  doc["ip"] = WiFi.localIP().toString();
  doc["rssi"] = WiFi.RSSI();

  String response;
  serializeJson(doc, response);

  server.send(200, "application/json", response);
}

void handleSensorData() {
  readSensors(); // Fresh sensor reading

  StaticJsonDocument<256> doc;

  doc["handDistance"] = deviceStatus.handDistance;
  doc["trashDistance"] = deviceStatus.trashDistance;
  doc["trashLevel"] = deviceStatus.trashLevel;
  doc["timestamp"] = millis();

  String response;
  serializeJson(doc, response);

  server.send(200, "application/json", response);
}

void handleOpenLid() {
  openLid();
  server.send(200, "application/json", "{\"status\":\"success\",\"message\":\"Lid opened\"}");
}

void handleCloseLid() {
  closeLid();
  server.send(200, "application/json", "{\"status\":\"success\",\"message\":\"Lid closed\"}");
}

void handleReset() {
  deviceStatus.totalOpens = 0;
  server.send(200, "application/json", "{\"status\":\"success\",\"message\":\"Device reset\"}");
}

void handleCSS() {
  String css = R"css(
body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    margin: 0;
    padding: 20px;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
}

.container {
    max-width: 1200px;
    margin: 0 auto;
}

h1 {
    text-align: center;
    margin-bottom: 30px;
    font-size: 2.5em;
    text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
}

.status-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
    gap: 20px;
    margin-bottom: 30px;
}

.status-card, .info-card {
    background: rgba(255, 255, 255, 0.1);
    backdrop-filter: blur(10px);
    border-radius: 15px;
    padding: 20px;
    box-shadow: 0 8px 32px rgba(0,0,0,0.1);
    border: 1px solid rgba(255, 255, 255, 0.2);
}

h3 {
    margin-top: 0;
    margin-bottom: 15px;
    font-size: 1.3em;
}

.status-indicator {
    width: 50px;
    height: 50px;
    border-radius: 50%;
    margin: 10px auto;
    background: #ff4757;
    transition: all 0.3s ease;
}

.status-indicator.active {
    background: #2ed573;
}

.level-bar {
    width: 100%;
    height: 30px;
    background: rgba(255, 255, 255, 0.2);
    border-radius: 15px;
    overflow: hidden;
    margin: 10px 0;
}

.level-fill {
    height: 100%;
    background: linear-gradient(90deg, #2ed573, #ffa502, #ff4757);
    transition: width 0.5s ease;
}

.info-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(400px, 1fr));
    gap: 20px;
}

button {
    background: rgba(255, 255, 255, 0.2);
    border: 2px solid rgba(255, 255, 255, 0.3);
    color: white;
    padding: 10px 20px;
    border-radius: 25px;
    cursor: pointer;
    font-size: 1em;
    transition: all 0.3s ease;
    margin-top: 10px;
}

button:hover {
    background: rgba(255, 255, 255, 0.3);
    transform: translateY(-2px);
}

p {
    margin: 8px 0;
}

span {
    color: #f8f9fa;
}
)css";

  server.send(200, "text/css", css);
}

void handleJS() {
  String js = R"js(
let updateInterval;

function updateDashboard() {
    fetch('/api/status')
        .then(response => response.json())
        .then(data => {
            // Update lid status
            const lidStatus = document.getElementById('lid-status');
            const lidButton = document.getElementById('lid-button');
            if (data.lidOpen) {
                lidStatus.classList.add('active');
                lidButton.textContent = 'Close Lid';
            } else {
                lidStatus.classList.remove('active');
                lidButton.textContent = 'Open Lid';
            }

            // Update trash level
            const trashLevel = document.getElementById('trash-level');
            const trashPercentage = document.getElementById('trash-percentage');
            trashLevel.style.width = data.trashLevel + '%';
            trashPercentage.textContent = data.trashLevel + '%';

            // Update hand detection
            const handStatus = document.getElementById('hand-status');
            const handDistance = document.getElementById('hand-distance');
            if (data.handDistance > 0 && data.handDistance <= 15) {
                handStatus.classList.add('active');
            } else {
                handStatus.classList.remove('active');
            }
            handDistance.textContent = data.handDistance.toFixed(1) + ' cm';

            // Update device info
            document.getElementById('ip-address').textContent = data.ip;
            document.getElementById('firmware').textContent = 'v' + data.firmware;
            document.getElementById('uptime').textContent = formatUptime(data.uptime);
            document.getElementById('total-opens').textContent = data.totalOpens;
            document.getElementById('wifi-signal').textContent = data.rssi + ' dBm';

            // Update last motion
            const lastMotion = document.getElementById('last-motion');
            const now = Date.now() / 1000;
            const timeDiff = now - (data.uptime - (Date.now() / 1000 - data.uptime));
            lastMotion.textContent = formatTimeAgo(timeDiff);
        })
        .catch(error => {
            console.error('Error updating dashboard:', error);
        });
}

function toggleLid() {
    const action = document.getElementById('lid-status').classList.contains('active') ? 'close' : 'open';
    const url = '/api/' + action + '-lid';

    fetch(url, { method: 'POST' })
        .then(response => response.json())
        .then(data => {
            console.log('Lid toggled:', data);
            updateDashboard();
        })
        .catch(error => {
            console.error('Error toggling lid:', error);
        });
}

function formatUptime(seconds) {
    const hours = Math.floor(seconds / 3600);
    const minutes = Math.floor((seconds % 3600) / 60);
    const secs = seconds % 60;
    return hours + 'h ' + minutes + 'm ' + secs + 's';
}

function formatTimeAgo(seconds) {
    if (seconds < 60) return 'Just now';
    if (seconds < 3600) return Math.floor(seconds / 60) + ' minutes ago';
    if (seconds < 86400) return Math.floor(seconds / 3600) + ' hours ago';
    return Math.floor(seconds / 86400) + ' days ago';
}

// Start updating dashboard
document.addEventListener('DOMContentLoaded', function() {
    updateDashboard();
    updateInterval = setInterval(updateDashboard, 2000);
});
)js";

  server.send(200, "application/javascript", js);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

// ========== UTILITY FUNCTIONS ==========
void printStatus() {
  static unsigned long lastPrint = 0;
  unsigned long currentTime = millis();

  // Print status every 5 seconds
  if (currentTime - lastPrint >= 5000) {
    Serial.println("📊 System Status:");
    Serial.print("  WiFi Status: ");
    Serial.println(WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected");

    Serial.print("  IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.print("  Hand Distance: ");
    Serial.print(deviceStatus.handDistance);
    Serial.println(" cm");

    Serial.print("  Trash Level: ");
    Serial.print(deviceStatus.trashLevel);
    Serial.println("%");

    Serial.print("  Lid Status: ");
    Serial.println(deviceStatus.lidOpen ? "Open" : "Closed");

    Serial.print("  Total Opens: ");
    Serial.println(deviceStatus.totalOpens);

    Serial.print("  Uptime: ");
    Serial.print(deviceStatus.uptime);
    Serial.println(" seconds");

    Serial.println("");

    lastPrint = currentTime;
  }
}
