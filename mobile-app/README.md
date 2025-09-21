# 📱 Smart Trashcan Mobile App

<div align="center">
  <h3>Professional React Native Android Application</h3>
  <p>Modern, intuitive mobile interface for IoT Smart Trashcan control and monitoring</p>

  ![React Native](https://img.shields.io/badge/React%20Native-0.70.6-blue)
  ![Android](https://img.shields.io/badge/Android-11+-green)
  ![Material Design](https://img.shields.io/badge/Material%20Design-3-purple)
  ![Redux](https://img.shields.io/badge/Redux-Toolkit-orange)
</div>

---

## 📋 Overview

This is a **professional-grade React Native mobile application** designed specifically for the Smart Trashcan IoT project. Built with modern development practices and Material Design 3 principles, it provides:

- **Real-time device monitoring** with live status updates
- **Remote lid control** via WiFi connectivity
- **Usage analytics** and statistics visualization
- **Professional UI/UX** with smooth animations
- **Cross-platform compatibility** (Android-first approach)
- **Offline functionality** with data caching

---

## ✨ Features

### 🎮 Core Functionality
- **Device Discovery**: Automatic detection of Smart Trashcan devices
- **Real-time Monitoring**: Live updates of trash level, lid status, and sensor data
- **Remote Control**: Open/close lid remotely via WiFi
- **Status Indicators**: Visual feedback for device connection and operation
- **Usage Analytics**: Track usage patterns and statistics

### 🎨 Professional UI/UX
- **Material Design 3**: Modern, clean interface following Google's design guidelines
- **Dark/Light Theme**: Automatic theme switching with manual override
- **Smooth Animations**: React Native Reanimated for fluid transitions
- **Responsive Layout**: Optimized for various Android screen sizes
- **Accessibility**: Screen reader support and touch target optimization

### 🔧 Advanced Features
- **Push Notifications**: Smart alerts for full trash, device offline, etc.
- **Offline Mode**: Cached data and functionality when offline
- **Data Export**: Export usage statistics and device logs
- **Settings Management**: Comprehensive configuration options
- **Multi-device Support**: Control multiple trashcans from one app

---

## 🛠️ Technical Stack

### Core Technologies
- **React Native 0.70.6**: Cross-platform mobile development
- **Redux Toolkit**: State management and data flow
- **React Navigation 6**: Navigation and routing
- **React Native Paper**: Material Design components
- **Axios**: HTTP client for API communication

### Development Tools
- **Android Studio**: Android development environment
- **Node.js 16+**: JavaScript runtime
- **Metro Bundler**: React Native bundler
- **React Native Debugger**: Debugging and development tools

### Libraries & Dependencies
```json
{
  "react-native-vector-icons": "^10.0.2",
  "react-native-gesture-handler": "^2.12.1",
  "react-native-reanimated": "^3.5.4",
  "react-native-chart-kit": "^6.12.0",
  "react-native-ble-plx": "^2.0.3",
  "react-native-permissions": "^3.10.1"
}
```

---

## 🚀 Quick Start Guide

### Prerequisites
- **Node.js**: 16.x or later
- **React Native CLI**: Install globally (`npm install -g react-native-cli`)
- **Android Studio**: Latest stable version
- **Android SDK**: API level 30+ (Android 11+)
- **Java Development Kit**: JDK 11 or later

### Installation Steps

1. **Clone and Navigate**
   ```bash
   git clone <repository-url>
   cd smart-trashcan/mobile-app
   ```

2. **Install Dependencies**
   ```bash
   npm install
   ```

3. **Configure Android Environment**
   ```bash
   # Install Android Studio
   # Set up Android SDK (API 30+)
   # Configure ANDROID_HOME environment variable
   ```

4. **Update Device Configuration**
   - Open `src/services/ApiService.js`
   - Update the device IP address and API endpoints
   - Configure WiFi settings if needed

5. **Run the Application**
   ```bash
   # For Android
   npx react-native run-android

   # For iOS (if needed)
   npx react-native run-ios
   ```

6. **Development Server**
   ```bash
   # Start Metro bundler
   npx react-native start

   # In another terminal, run the app
   npx react-native run-android
   ```

---

## 📁 Project Structure

```
📦 mobile-app/
├── 📄 package.json              # Dependencies and scripts
├── 📄 README.md                 # This file
├── 📄 index.js                  # App entry point
├── 📁 android/                  # Android-specific files
├── 📁 src/                      # Source code
│   ├── 📄 App.js               # Main app component
│   ├── 📁 components/          # Reusable UI components
│   │   ├── 📄 DeviceCard.js    # Device status card
│   │   ├── 📄 ControlButton.js # Remote control buttons
│   │   ├── 📄 AnalyticsChart.js # Usage charts
│   │   └── 📄 SettingsItem.js  # Settings list items
│   ├── 📁 screens/             # App screens
│   │   ├── 📄 DashboardScreen.js
│   │   ├── 📄 ControlScreen.js
│   │   ├── 📄 AnalyticsScreen.js
│   │   └── 📄 SettingsScreen.js
│   ├── 📁 services/            # API and external services
│   │   ├── 📄 ApiService.js    # HTTP API client
│   │   ├── 📄 DeviceService.js # Device communication
│   │   └── 📄 NotificationService.js
│   ├── 📁 store/               # Redux state management
│   │   ├── 📄 store.js         # Redux store configuration
│   │   └── 📁 slices/          # Redux slices
│   ├── 📁 utils/               # Helper functions
│   │   ├── 📄 theme.js         # App theme configuration
│   │   ├── 📄 constants.js     # App constants
│   │   └── 📄 helpers.js       # Utility functions
│   └── 📁 assets/              # Images and icons
└── 📁 __tests__/               # Test files
```

---

## ⚙️ Configuration

### Device Setup
1. **IP Address Configuration**
   - Open `src/services/ApiService.js`
   - Update `BASE_URL` with your ESP32 device IP
   - Configure API endpoints

2. **WiFi Settings**
   - Ensure device and phone are on same network
   - Configure network timeout settings
   - Set up auto-reconnection parameters

3. **Notification Settings**
   - Configure push notification permissions
   - Set up notification categories
   - Customize alert preferences

### Theme Customization
- Modify `src/utils/theme.js` for custom colors
- Update Material Design components
- Configure dark/light mode preferences

---

## 🧪 Testing

### Unit Tests
```bash
# Run Jest tests
npm test

# Run specific test file
npm test DeviceCard.test.js
```

### Integration Tests
```bash
# Test API endpoints
npm run test:api

# Test device connectivity
npm run test:device
```

### Manual Testing Checklist
- [ ] Device discovery and pairing
- [ ] Real-time status updates
- [ ] Remote lid control
- [ ] Push notifications
- [ ] Offline functionality
- [ ] Theme switching
- [ ] Settings persistence

---

## 📱 Android Deployment

### Debug Build
```bash
# Generate debug APK
npx react-native run-android --variant=debug

# Install on connected device
adb install android/app/build/outputs/apk/debug/app-debug.apk
```

### Release Build
```bash
# Clean and build release
cd android
./gradlew clean
./gradlew assembleRelease

# Generate signed bundle (AAB)
./gradlew bundleRelease
```

### Google Play Store
1. **Prepare Store Listing**
   - Create compelling app description
   - Add screenshots and feature graphics
   - Set up pricing and distribution

2. **Generate Signed Release**
   - Create keystore for app signing
   - Configure signing in `android/app/build.gradle`
   - Generate AAB file for Play Store

3. **Beta Testing**
   - Set up beta testing channels
   - Distribute to internal testers
   - Gather feedback and bug reports

---

## 🐛 Troubleshooting

### Common Issues

**Metro Bundler Not Starting**
```bash
# Clear Metro cache
npx react-native start --reset-cache

# Clear npm cache
npm start -- --reset-cache
```

**Android Build Issues**
```bash
# Clean Android build
cd android && ./gradlew clean

# Clear React Native cache
npx react-native clean
```

**Device Connection Issues**
- Ensure device and phone on same WiFi network
- Check firewall settings
- Verify ESP32 IP address configuration
- Test API endpoints with browser/curl

**Permission Issues**
```bash
# Check Android permissions
adb shell dumpsys package com.smarttrashcan | grep permission

# Grant permissions manually
adb shell pm grant com.smarttrashcan android.permission.ACCESS_FINE_LOCATION
```

### Debug Mode
- Enable remote debugging in React Native
- Use React Native Debugger for Redux inspection
- Check Metro bundler console for errors
- Monitor Android logs with `adb logcat`

---

## 🤝 Contributing

### Development Workflow
1. Fork the repository
2. Create feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open Pull Request

### Code Standards
- Follow React Native best practices
- Use TypeScript for type safety
- Implement proper error handling
- Add JSDoc comments for functions
- Follow Material Design guidelines

### Testing Requirements
- Unit tests for all components
- Integration tests for API calls
- Manual testing on multiple devices
- Performance testing for animations

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](../LICENSE) file for details.

---

## 📞 Support

### Development Support
- **GitHub Issues**: [Report bugs](https://github.com/your-username/smart-trashcan/issues)
- **Discussions**: [Feature requests](https://github.com/your-username/smart-trashcan/discussions)
- **Email**: mobile-dev@smarttrashcan.dev

### User Support
- **Documentation**: [Setup Guide](SETUP-GUIDE.md)
- **FAQ**: [Frequently Asked Questions](FAQ.md)
- **Community Forum**: [Join Discussion](https://github.com/your-username/smart-trashcan/discussions)

---

<div align="center">

**Made with ❤️ for Android users**

[⭐ Star this repo](https://github.com/your-username/smart-trashcan) •
[🍴 Fork for your project](#) •
[🐛 Report issues](https://github.com/your-username/smart-trashcan/issues) •
[💬 Join discussion](https://github.com/your-username/smart-trashcan/discussions)

</div>

---

**App Version**: 1.0.0 |
**Last Updated**: December 2024 |
**Target Platform**: Android 11+ |
**Development Status**: 🚧 Active Development
