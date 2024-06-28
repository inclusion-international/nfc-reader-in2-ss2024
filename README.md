# NFC Reader for AsTeRICS-Grid

## Problem Description
Assistive Augmentative Communication (AAC) solutions, such as AsTeRICS-Grid, offer essential communication aids to individuals with speech and language impairments. However, the reliance on visual-based or complex input methods can limit accessibility for users with visual impairments, including blind individuals. There's a significant need for intuitive, non-visual alternative input methods to enhance interaction with AAC software for a broader range of users.

## Proposed Solution
Create an innovative Near Field Communication (NFC) reader that serves as an alternative and accessible input method for the AsTeRICS-Grid, an open-source AAC software. By leveraging NFC technology, users can interact with the AAC software through physical NFC tags, which are identifiable by touch. The project encompasses two complementary approaches:

1. **Hardware/Software NFC Reader**:
   - Design and build either a handheld NFC reader device or an extension for FABI, as an alternative input device for AsTeRICS-Grid. This involves creating a microcontroller-based system equipped with an NFC chip and custom electronic circuitry.
   - The device could be designed with tactile markers for easy operation by blind users, enabling them to read NFC tags and transmit the information to AsTeRICS-Grid via Web-Bluetooth or similar technologies.

2. **Android App with NFC**:
   - For users without access to the custom NFC reader, an Android app will replicate the device's functionality, utilizing the smartphone's built-in NFC reading capabilities.
   - The app will be designed with accessibility features (potentially including voice feedback and simple, intuitive gestures), ensuring blind and visually impaired users can effectively interact with it.

## Project Components

### Pico W NFC Reader

#### Hardware Components
- **Microcontroller**: Pico W
- **NFC Module**: V3 (PN532)

#### Connection Details
To connect the NFC Module V3 (PN532) to the Pico W via I2C, follow these steps:

1. **Wiring Connections**:
   - PN532 SDA to Pico W GPIO2
   - PN532 SCL to Pico W GPIO3
   - PN532 IRQ to Pico W GPIO6
   - PN532 RSTO to Pico W GPIO7
   - PN532 VCC to Pico W 3.3V
   - PN532 GND to Pico W GND

2. **Power Supply**:
   - Connect the VCC of the PN532 to the 3.3V pin of the Pico W.
   - Connect the GND of the PN532 to the GND pin of the Pico W.

#### Pico W Firmware
The firmware for the Pico W is written in C++ using the Arduino framework. The code handles NFC tag detection and data processing. The NFC reader inputs are currently processed as Huffman codes due to limitations in establishing a Bluetooth connection.

**Libraries Used**:
- `Wire.h`
- `SPI.h`
- `Adafruit_PN532.h`
- `Keyboard.h`

**Key Functionalities**:
- **Tag Detection**: The firmware continuously scans for NFC tags.
- **Data Retrieval**: Upon detecting a tag, it reads the data stored on the tag.
- **Data Processing**: The data is parsed to extract the object name and Huffman code for the grid.

#### Searching Data on NFC Tags
The data stored on the NFC tags includes the name of the object and the Huffman code for the grid. The data is delimited by specific markers:

- **Object Name**: The name of the object is stored between the markers `$AG$` and `$FE$`.
- **Huffman Code**: The Huffman code for the grid is stored between the markers `$AGT$` and `$FE$`.

The firmware searches for these markers to retrieve the relevant information:
1. **Search for Object Name**:
   - Scan the data for the `$AG$` marker.
   - Collect the text until the `$FE$` marker is found.
   - This collected text is the name of the object.
2. **Search for Huffman Code**:
   - Scan the data for the `$AGT$` marker.
   - Collect the text until the `$FE$` marker is found.
   - This collected text is the Huffman code for the grid.

#### 3D Printed Enclosures
We have designed 3D printable enclosures for the NFC reader. The files for these designs are included in the repository. During the testing phase, we used PLA with 5-15% infill. For actual user application, a food-safe filament should be used to ensure safety.

### NFC Tags
We currently use NTAG215 tags, but the system is also compatible with NTAG213, NTAG216, and MIFARE tags. It is crucial that the necessary information is stored between the correct markers on the tags:

- **Object Name**: Stored between `$AG$` and `$FE$`.
- **Huffman Code**: Stored between `$AGT$` and `$FE$`.

#### 3D Objects for NFC Tags
We have also designed simple 3D objects to house the NFC tags. These objects are based on a cylinder with a diameter of 5 cm and a height of 2.5 cm. Different shapes, such as domes, cones, and cups, are placed on top of this cylindrical base. These designs help users easily identify the NFC tags by touch. The STL files for these objects are provided in the repository.


### Android App
The Android app is designed to provide similar functionality as the hardware NFC reader. The app uses the smartphone's built-in NFC capabilities and is designed with accessibility features to ensure usability by blind and visually impaired users. However, the integration with AsTeRICS-Grid and complete data processing from the NFC tags are not yet implemented. The app source code and installation instructions are provided in the `android_app` directory of this repository.

## Future Improvements
In the future, both the Pico W and the Android app will be able to connect to the AsTeRICS-Grid via Bluetooth. NFC tags will store complete grid information, allowing the device to be used on any PC without additional setup.

## Documentation
Comprehensive documentation and user guides are available in the `docs` directory. These guides are designed to support users in utilizing the NFC reader and app with AsTeRICS-Grid.

## Contribution
We welcome contributions to improve this project. Please refer to the `CONTRIBUTING.md` file for guidelines on how to contribute.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

---

Feel free to reach out if you have any questions or need further assistance with the project setup. Happy building!
