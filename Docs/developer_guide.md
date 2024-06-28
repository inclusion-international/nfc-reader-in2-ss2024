# Developer Guide

## Project Structure
- **Firmware**: Located in the `firmware` directory.
- **Android App**: Located in the `android_app` directory.
- **3D Models**: Located in the `3d_models` directory.

## Setting Up the Development Environment
1. **Clone the Repository**: Use `git clone` to download the project repository.
2. **Install Dependencies**: Use the Arduino Library Manager and Android Studio to install necessary dependencies.
3. **Build the Firmware**: Open the firmware code in the Arduino IDE, select the appropriate board and port, and upload the code to the Pico W.
4. **Build the Android App**: Open the Android app project in Android Studio, configure the SDK, and build the app.

## Code Overview for the Pico W Firmware
- **Main Functions**: Description of the main functions, including `setup()`, `loop()`, `detectTag()`, and data processing functions.
- **Libraries Used**: Details on the libraries used (`Wire.h`, `SPI.h`, `Adafruit_PN532.h`, `Keyboard.h`).

## Code Overview for the Android App
- **Main Components**: Description of the main components and activities in the app.
- **NFC Integration**: Details on how the app integrates with the device’s NFC hardware.

## Guidelines for Adding New Features
- **Feature Requests**: How to submit and prioritize feature requests.
- **Development Standards**: Coding standards, documentation requirements, and testing procedures.
