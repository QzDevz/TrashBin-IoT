/*
 * 🤖 Arduino UNO Smart Trashcan Prototype
 * Professional-grade smart trashcan with automatic lid operation
 *
 * Features:
 * - Ultrasonic hand detection (<15cm threshold)
 * - Servo-controlled sliding lid mechanism
 * - Real-time trash level monitoring
 * - LED status indicators (PWM controlled)
 * - Serial debugging interface
 * - Non-blocking sensor reading
 *
 * Hardware Requirements:
 * - Arduino UNO R3
 * - SG90 Servo Motor
 * - HC-SR04 Ultrasonic Sensors (x2)
 * - Red LED (5mm) + 220Ω resistor
 * - 9V Battery + Power adapter
 *
 * Version: 1.0.0
 * Last Updated: December 2024
 */

#include <Servo.h>

// ========== PIN DEFINITIONS ==========
#define SERVO_PIN           9     // Servo motor control pin
#define LED_PIN             10    // Status LED pin (PWM)
#define TRIG_PIN_HAND       6     // Hand detection trigger pin
#define ECHO_PIN_HAND       7     // Hand detection echo pin
#define TRIG_PIN_TRASH      4     // Trash level trigger pin
#define ECHO_PIN_TRASH      5     // Trash level echo pin

// ========== CONFIGURATION ==========
#define HAND_DETECTION_THRESHOLD  15  // Distance in cm for hand detection
#define LID_OPEN_ANGLE           90   // Servo angle for open position
#define LID_CLOSE_ANGLE          0    // Servo angle for closed position
#define AUTO_CLOSE_DELAY         5000 // Auto-close delay in milliseconds
#define SENSOR_READ_INTERVAL     100  // Sensor reading interval in milliseconds
#define LED_UPDATE_INTERVAL      50   // LED update interval in milliseconds

// ========== GLOBAL VARIABLES ==========
Servo lidServo;                   // Servo object for lid control

// Timing variables
unsigned long lastSensorRead = 0;
unsigned long lastLedUpdate = 0;
unsigned long lidOpenTime = 0;
bool lidOpen = false;

// Sensor variables
float handDistance = 0;
float trashDistance = 0;
int trashLevel = 0;              // 0-100 percentage

// LED variables
int ledBrightness = 0;           // 0-255 PWM value

// ========== SETUP FUNCTION ==========
void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("🤖 Smart Trashcan - Arduino UNO Prototype");
  Serial.println("=====================================");

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

  // Initial sensor reading
  readSensors();

  Serial.println("✅ System ready!");
  Serial.println("📱 Wave hand near sensor to open lid");
  Serial.println("");
}

// ========== MAIN LOOP ==========
void loop() {
  unsigned long currentTime = millis();

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

  // Print status to serial monitor
  printStatus();

  // Small delay for stability
  delay(10);
}

// ========== SENSOR FUNCTIONS ==========
void readSensors() {
  // Read hand detection sensor
  handDistance = readUltrasonicDistance(TRIG_PIN_HAND, ECHO_PIN_HAND);

  // Read trash level sensor
  trashDistance = readUltrasonicDistance(TRIG_PIN_TRASH, ECHO_PIN_TRASH);

  // Calculate trash level (assuming 20cm max depth)
  trashLevel = constrain(map(trashDistance, 2, 20, 100, 0), 0, 100);
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
  if (handDistance > 0 && handDistance <= HAND_DETECTION_THRESHOLD) {
    if (!lidOpen) {
      openLid();
      Serial.println("✋ Hand detected - Opening lid");
    }
    lidOpenTime = currentTime; // Reset auto-close timer
  }

  // Auto-close lid after delay
  if (lidOpen && (currentTime - lidOpenTime >= AUTO_CLOSE_DELAY)) {
    closeLid();
    Serial.println("⏰ Auto-closing lid");
  }
}

void openLid() {
  lidServo.write(LID_OPEN_ANGLE);
  lidOpen = true;
  Serial.print("✅ Lid opened at angle: ");
  Serial.println(LID_OPEN_ANGLE);
}

void closeLid() {
  lidServo.write(LID_CLOSE_ANGLE);
  lidOpen = false;
  Serial.println("✅ Lid closed");
}

// ========== LED CONTROL FUNCTIONS ==========
void updateLED() {
  // Calculate LED brightness based on trash level
  if (trashLevel < 30) {
    // Empty - dim green (simulated with low brightness)
    ledBrightness = 50;
  } else if (trashLevel < 70) {
    // Half full - medium orange (simulated with medium brightness)
    ledBrightness = 150;
  } else {
    // Full - bright red (simulated with high brightness)
    ledBrightness = 255;
  }

  // Apply brightness with PWM
  analogWrite(LED_PIN, ledBrightness);
}

// ========== UTILITY FUNCTIONS ==========
void printStatus() {
  static unsigned long lastPrint = 0;
  unsigned long currentTime = millis();

  // Print status every 2 seconds
  if (currentTime - lastPrint >= 2000) {
    Serial.println("📊 System Status:");
    Serial.print("  Hand Distance: ");
    Serial.print(handDistance);
    Serial.println(" cm");

    Serial.print("  Trash Level: ");
    Serial.print(trashLevel);
    Serial.println("%");

    Serial.print("  Lid Status: ");
    Serial.println(lidOpen ? "Open" : "Closed");

    Serial.print("  LED Brightness: ");
    Serial.println(ledBrightness);

    Serial.println("  Memory Usage: " + String(freeMemory()) + " bytes free");
    Serial.println("");

    lastPrint = currentTime;
  }
}

int freeMemory() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

// ========== INTERRUPT HANDLERS (Optional) ==========
// Add interrupt-based sensor reading for better responsiveness
// void setupInterrupts() {
//   attachInterrupt(digitalPinToInterrupt(ECHO_PIN_HAND), handleHandDetection, CHANGE);
// }

// void handleHandDetection() {
//   // Handle hand detection interrupt
//   // Implementation for advanced users
// }
