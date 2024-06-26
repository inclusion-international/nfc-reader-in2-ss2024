#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <Keyboard.h>

#define PN532_SCK  (2)
#define PN532_MOSI (3)
#define PN532_SS   (4)
#define PN532_MISO (5)

#define PN532_IRQ   (6)
#define PN532_RESET (7)

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

#define MAX_DATA_LENGTH 512 // Maximum data length to store
#define NTAG2XX_PAGE_SIZE 4 // Page size for NTAG2xx
#define NTAG2XX_CONFIG_PAGE 3 // Page containing configuration register for NTAG2xx

void setup(void) {
  Serial.begin(115200);
  Keyboard.begin();
  while (!Serial) delay(10); // for Leonardo/Micro/Zero

  Serial.println("Hello!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);

  Serial.println("Waiting for an ISO14443A Card ...");
}

void loop(void) {
  uint8_t success;
  uint8_t uid[7];  // Buffer to store the returned UID (up to 7 bytes for ISO14443A)
  uint8_t uidLength;  // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // Wait for a card. When one is found, 'uid' will be populated with
  // the UID, and 'uidLength' will indicate the size of the UID.
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println("");

    uint8_t collectedData[MAX_DATA_LENGTH]; // Array to collect data
    uint16_t collectedLength = 0; // Length of collected data

    // Read data from the card
    if (uidLength == 4) {
      // MIFARE Classic card
      for (uint8_t block = 4; block < 64; block++) {
        uint8_t data[16];
        success = nfc.mifareclassic_ReadDataBlock(block, data);

        if (success) {
          // Append block data to collected data
          memcpy(collectedData + collectedLength, data, 16);
          collectedLength += 16;
        } else {
          Serial.println("Unable to read the requested block!");
          break;
        }
      }
    } else if (uidLength == 7) {
      // NTAG card
      uint16_t estimatedPages = 42; // Default estimated pages for NTAG2xx

      // Read page 3 to determine NTAG type
      uint8_t configData[NTAG2XX_PAGE_SIZE];
      success = nfc.ntag2xx_ReadPage(NTAG2XX_CONFIG_PAGE, configData);

      if (success) {
        uint8_t ntagType = configData[2];
        switch (ntagType) {
          case 0x12: // NTAG213
            estimatedPages = 39;
            break;
          case 0x3E: // NTAG215
            estimatedPages = 129;
            break;
          case 0x6D: // NTAG216
            estimatedPages = 225;
            break;
          default:
            Serial.println("Unknown NTAG type!");
            break;
        }

        // Read data pages based on estimated pages
        for (uint16_t i = 4; i < estimatedPages; i++) {
          uint8_t data[NTAG2XX_PAGE_SIZE];
          success = nfc.ntag2xx_ReadPage(i, data);

          if (success) {
            // Append page data to collected data
            memcpy(collectedData + collectedLength, data, NTAG2XX_PAGE_SIZE);
            collectedLength += NTAG2XX_PAGE_SIZE;
          } else {
            Serial.println("Unable to read the requested page!");
            break;
          }
        }
      } else {
        Serial.println("Unable to read configuration page!");
      }
    }

    if (collectedLength > 0) {
      // Search for "$AG$" marker in collected data
      bool foundDataAG = searchAndPrintAGText(collectedData, collectedLength);
      if (!foundDataAG) {
        Serial.println("Dieser Tag enthält keine Daten für das AstericsGrid-System (AG)");
      }
      // Search for "$AGT$" marker in collected data
      bool foundDataAGT = searchAndPrintAGTText(collectedData, collectedLength);
      if (!foundDataAGT) {
        Serial.println("Dieser Tag enthält keine Daten für das AstericsGrid-System (AGT)");
      }
    } else {
      Serial.println("No data read from the card!");
    }

    // Wait for the tag to be removed before scanning again
    Serial.println("Waiting for tag removal...");
    waitForTagRemoval();
    Serial.println("Tag removed. Waiting for a new tag...");
  }
}

bool searchAndPrintAGText(uint8_t* data, uint16_t length) {
  bool foundAG = false; // Flag to indicate if $AG$ marker has been found
  bool foundData = false; // Flag to indicate if data between $AG$ and $FE$ has been found
  String collectedText = ""; // String to collect text

  for (uint16_t i = 0; i < length; i++) {
    if (!foundAG) {
      // Search for the "$AG$" marker
      if (i + 3 < length && data[i] == 0x24 && data[i + 1] == 0x41 && data[i + 2] == 0x47 && data[i + 3] == 0x24) {
        // Found the start marker $AG$
        foundAG = true;
        i += 3; // Skip the marker
      }
    } else {
      // Collect the text until "$FE$" is found
      if (i + 3 < length && data[i] == 0x24 && data[i + 1] == 0x46 && data[i + 2] == 0x45 && data[i + 3] == 0x24) {
        // Found the end marker "$FE$"
        foundAG = false;
        foundData = true;
        // Print the collected text
        Serial.print("Collected Text: ");
        Serial.println(collectedText);
        collectedText = ""; // Clear collected text for next use
        i += 3; // Skip the end marker
      } else {
        // Append the character to collected text
        collectedText += char(data[i]);
      }
    }
  }
  return foundData;
}

bool searchAndPrintAGTText(uint8_t* data, uint16_t length) {
  bool foundAGT = false; // Flag to indicate if $AGT$ marker has been found
  bool foundData = false; // Flag to indicate if data between $AGT$ and $FE$ has been found
  String collectedText = ""; // String to collect text

  for (uint16_t i = 0; i < length; i++) {
    if (!foundAGT) {
      // Search for the "$AGT$" marker
      if (i + 4 < length && data[i] == 0x24 && data[i + 1] == 0x41 && data[i + 2] == 0x47 && data[i + 3] == 0x54 && data[i + 4] == 0x24) {
        // Found the start marker $AGT$
        foundAGT = true;
        i += 4; // Skip the marker
      }
    } else {
      // Collect the text until "$FE$" is found
      if (i + 3 < length && data[i] == 0x24 && data[i + 1] == 0x46 && data[i + 2] == 0x45 && data[i + 3] == 0x24) {
        // Found the end marker "$FE$"
        foundAGT = false;
        foundData = true;
        // Print the collected text
        Serial.print("Collected Numbers: ");
        Serial.println(collectedText);
        // Process and type the collected text as numbers
        typeNumbersAndAdditionalKeys(collectedText);
        collectedText = ""; // Clear collected text for next use
        i += 3; // Skip the end marker
      } else {
        // Append the character to collected text
        collectedText += char(data[i]);
      }
    }
  }
  return foundData;
}

void typeNumbersAndAdditionalKeys(String text) {
  for (uint16_t i = 0; i < text.length(); i++) {
    if (isDigit(text[i])) {
      Keyboard.write(text[i]);
      delay(100); // 100 ms delay between keystrokes
    }
  }
  // Type the additional keys '1' and '3'
  Keyboard.write('1');
  delay(100);
  Keyboard.write('3');
  delay(100);
}

void waitForTagRemoval() {
  uint8_t uid[7];  // Buffer to store the returned UID (up to 7 bytes for ISO14443A)
  uint8_t uidLength;

  while (true) {
    // Check if a card is still present
    bool tagPresent = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

    // If no tag is present, break the loop
    if (!tagPresent) {
      Serial.println("Tag removal detected.");
      break;  // Tag was removed
    }
    Serial.println("Tag still present...");
    delay(100);
  }

  // Wait for a short moment to ensure the tag is removed
  Serial.println("Ensuring tag is removed...");
  delay(1000);

  // Reset all variables
  memset(uid, 0, sizeof(uid));
  uidLength = 0;
}
