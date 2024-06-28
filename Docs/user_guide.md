# User Guide

## Grid Setup
1. **Create an Account**: On the first use, create an account on the AsTeRICS-Grid website.
2. **Import NFC-Grid**: From the repository, import the NFC-Grid as an example. Ensure to select "Import custom data from file."
3. **Configure Huffman Coding**: Enter the correct Huffman coding in the code and on the tags. Adjust both the `#define DELETE` function at the beginning of the code and the tags to match the Huffman code displayed in the Grid.

## Connecting the NFC Reader to a PC
1. **Connect via USB**: Use a USB cable to connect the Pico W to your computer.
2. **Install Necessary Drivers**: Ensure that any necessary drivers for the Pico W are installed on your computer.
3. **Open AsTeRICS-Grid**: Open the AsTeRICS-Grid software on your computer with the NFC-Grid example loaded.
4. **Test the Connection**: Place an NFC tag near the reader and check if the data is correctly transmitted to AsTeRICS-Grid.

## Using the Android App
1. **Install the App**: Download and install the NFC Reader app on your Android device.
2. **Enable NFC**: Ensure that NFC is enabled on your Android device.
3. **Open the App**: Launch the NFC Reader app.
4. **Scan an NFC Tag**: Place an NFC tag near your device’s NFC sensor and follow the prompts in the app.

## Troubleshooting Common Issues
- **No Response from the NFC Reader**: Ensure all connections are secure and the Pico W is powered.
- **Data Not Displaying in AsTeRICS-Grid**: Verify that the correct firmware is uploaded and the drivers are installed.
- **Android App Not Scanning Tags**: Make sure NFC is enabled on your device and the tag is correctly positioned near the sensor.
