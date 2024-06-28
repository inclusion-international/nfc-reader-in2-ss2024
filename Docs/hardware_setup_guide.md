# Hardware Setup Guide

## List of Hardware Components
- Pico W Microcontroller
- NFC Module V3 (PN532)
- USB Cable
- Breadboard and Wires (for prototyping)
- Power Supply (if needed for standalone operation)

## Wiring Diagrams and Connection Details
1. **NFC Module to Pico W Connections (I2C)**:
   - PN532 SDA to Pico W GPIO2
   - PN532 SCL to Pico W GPIO3
   - PN532 IRQ to Pico W GPIO6
   - PN532 RSTO to Pico W GPIO7
   - PN532 VCC to Pico W 3.3V
   - PN532 GND to Pico W GND

## 3D Printing Settings and Assembly Instructions
### Printing Settings
- **Material**: PLA for testing, food-safe filament for final use
- **Infill**: 5-15%
- **Layer Height**: 0.2 mm
- **Print Speed**: 50 mm/s

### Assembly Instructions
1. **Print the Enclosures**: Use the provided STL files to print the enclosure parts.
2. **Assemble the Hardware**: Place the Pico W and NFC Module inside the printed enclosure.
3. **Secure the Components**: Ensure all components are securely fitted and the connections are stable.
