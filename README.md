# 🤖 Arduino UNO Smart Sliding-Lid Trashcan

<div align="center">
  <h3>Professional IoT-Enabled Waste Management System</h3>
  <p>Intelligent trashcan with automatic lid operation, real-time monitoring, and professional mobile application</p>

  ![Project Status](https://img.shields.io/badge/Status-Active%20Development-brightgreen)
  ![Version](https://img.shields.io/badge/Version-1.0.0-blue)
  ![Platform](https://img.shields.io/badge/Platform-Arduino%20UNO%20%7C%20ESP32-orange)
  ![Mobile](https://img.shields.io/badge/Mobile-React%20Native%20%7C%20Android-purple)
</div>

---

## 📋 Table of Contents

- [Project Overview](#-project-overview)
- [Features](#-features)
- [Hardware Requirements](#-hardware-requirements)
- [Software Requirements](#-software-requirements)
- [Quick Start Guide](#-quick-start-guide)
- [Project Structure](#-project-structure)
- [Documentation](#-documentation)
- [Contributing](#-contributing)
- [License](#-license)

---

## 🎯 Project Overview

This project creates a **professional-grade smart trashcan** using Arduino UNO/ESP32 that features:
- **Automatic lid operation** - Opens when hand is detected within 15cm
- **Real-time trash level monitoring** - Ultrasonic sensor-based fill level detection
- **Professional mobile application** - React Native Android app with modern UI
- **IoT connectivity** - WiFi-enabled remote monitoring and control
- **Visual status indicators** - PWM-controlled LED brightness indicators
- **Web dashboard** - Real-time monitoring via web interface

### 🎯 Current Status
- **Phase**: Development
- **Status**: 🚧 **ACTIVE DEVELOPMENT**
- **Focus**: Professional Android Application & IoT Integration

---

## ✨ Features

### Core Functionality
- ✅ **Hand Detection**: Ultrasonic sensor detects hands within 15cm
- ✅ **Automatic Lid Control**: Servo-powered sliding mechanism
- ✅ **Trash Level Monitoring**: Real-time fill level detection
- ✅ **LED Status Indicators**: Visual feedback (empty/half/full)
- ✅ **Auto-Close Timer**: 5-second automatic lid closure
- ✅ **Serial Debugging**: Real-time status monitoring

### IoT & Connectivity
- ✅ **WiFi Connectivity**: ESP32-based wireless communication
- ✅ **Web Dashboard**: Real-time monitoring interface
- ✅ **REST API**: HTTP endpoints for external integration
- ✅ **mDNS Support**: Local network discovery
- ✅ **Remote Control**: Web-based lid operation

### Professional Mobile App
- ✅ **React Native Android**: Professional cross-platform app
- ✅ **Material Design**: Modern, intuitive user interface
- ✅ **Real-time Monitoring**: Live status updates
- ✅ **Remote Control**: Wireless lid operation
- ✅ **Usage Analytics**: Statistics and insights
- ✅ **Push Notifications**: Smart alerts and reminders
- ✅ **Device Management**: Easy setup and configuration

---

## 🛠️ Hardware Requirements

### Core Components
| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino UNO R3 | 1 | Main microcontroller |
| ESP32 Dev Board | 1 | IoT connectivity version |
| SG90 Servo Motor | 1 | Lid control mechanism |
| HC-SR04 Ultrasonic | 2 | Hand detection & level monitoring |
| Red LED (5mm) | 1 | Status indicator |
| 220Ω Resistor | 1 | LED current limiting |
| 9V Battery | 1 | Power supply |
| Breadboard | 1 | Prototyping |
| Jumper Wires | 20+ | Connections |

### Mechanical Components
- Small container/box (trashcan body)
- Sliding lid mechanism
- Servo mounting hardware
- Sensor mounting brackets
- Power switch and enclosure

---

## 💻 Software Requirements

### Development Tools
- **Arduino IDE**: 1.8.19 or later
- **Node.js**: 16.x or later
- **React Native**: 0.70+
- **Android Studio**: Latest stable
- **Git**: Latest version

### Required Libraries
```arduino
// Arduino Libraries
#include <Servo.h>           // Servo motor control
#include <WiFi.h>            // ESP32 WiFi (IoT version)
#include <WebServer.h>       // Web server functionality
#include <ESPmDNS.h>         // Local network discovery
```

### Mobile App Dependencies
```json
{
  "react": "18.2.0",
  "react-native": "0.70.6",
  "@react-navigation/native": "^6.1.0",
  "axios": "^1.2.0",
  "redux": "^8.0.5"
}
```

---

## 🚀 Quick Start Guide

### 1. Repository Setup
```bash
git clone <repository-url>
cd smart-trashcan
npm install
```

### 2. Arduino Development
```bash
# Install Arduino IDE
# Add ESP32 board support via Board Manager
# Open software/src/arduino-uno-prototype.ino
# Upload to Arduino UNO
```

### 3. Mobile App Setup
```bash
cd mobile-app
npm install
npx react-native run-android
```

### 4. Testing
- Wave hand near sensor → Lid opens
- Add objects to trash → LED brightness changes
- Monitor via Serial/Bluetooth/Mobile app

---

## 📁 Project Structure

```
📦 Smart Trashcan Project
├── 📄 README.md                          # Project overview
├── 📄 TODO.md                           # Development roadmap
├── 📄 PROJECT-SUMMARY.md                # Complete documentation
├── 📁 hardware/                         # Mechanical designs
├── 📁 docs/                            # Documentation
│   ├── 📄 hardware-build-guide.md      # Assembly instructions
│   ├── 📄 wiring-diagram.md           # Circuit diagrams
│   ├── 📄 software-documentation.md   # Code documentation
│   └── 📄 troubleshooting-guide.md    # Problem solving
├── 📁 software/                        # Arduino firmware
│   └── 📁 src/                        # Source code
│       ├── 📄 arduino-uno-prototype.ino
│       └── 📄 esp32-iot-version.ino
├── 📁 mobile-app/                      # React Native app
│   ├── 📄 package.json                # Dependencies
│   ├── 📄 README.md                   # App documentation
│   ├── 📁 src/                       # Source code
│   │   ├── 📄 App.js                 # Main component
│   │   ├── 📁 components/            # UI components
│   │   ├── 📁 screens/               # App screens
│   │   ├── 📁 services/              # API services
│   │   └── 📁 utils/                 # Utilities
│   └── 📁 assets/                    # Images & icons
└── 📁 assets/                         # Project assets
```

---

## 📚 Documentation

### 📖 Complete Guides
- **[Hardware Build Guide](docs/hardware-build-guide.md)** - Step-by-step assembly
- **[Wiring Diagram](docs/wiring-diagram.md)** - Complete circuit reference
- **[Software Documentation](docs/software-documentation.md)** - Code and API docs
- **[Mobile App Guide](mobile-app/README.md)** - App setup and features
- **[Troubleshooting](docs/troubleshooting-guide.md)** - Common solutions

### 🎥 Video Resources
- [Assembly Tutorial](#) - Coming soon
- [Software Setup](#) - Coming soon
- [Mobile App Demo](#) - Coming soon

---

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guide](CONTRIBUTING.md).

### Development Workflow
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

### Code Style
- Follow Arduino style guidelines
- Use meaningful variable names
- Add comments for complex logic
- Test all functionality

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 📞 Support & Contact
- **Email**: mahardikaputr47@gmail.com

---

<div align="center">

**Made with ❤️ for a smarter, cleaner world**

[⭐ Star this repo](https://github.com/your-username/smart-trashcan) •
[🍴 Fork for your project](#) •
[🐛 Report issues](https://github.com/your-username/smart-trashcan/issues) •
[💬 Join discussion](https://github.com/your-username/smart-trashcan/discussions)

</div>

---

**Project Status**: 🚧 **Active Development** |
**Last Updated**: 21 Sept 2025 |
**Version**: 1.0.0
