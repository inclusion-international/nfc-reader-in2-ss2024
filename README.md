# nfc-reader-in2-ss2024


## Projektbeschreibung

Dieses Projekt ist ein NFC-Reader, der mit einem Raspberry Pi Pico W und einem NFC-Modul erstellt wurde. Es ermöglicht das Auslesen von NFC-Tags, was in vielen Anwendungsfällen nützlich sein kann, wie z.B. Zugangskontrollsysteme, elektronische Zahlungssysteme oder Informationsabrufsysteme.

## Problemstellung

Die steigende Verbreitung von NFC-Technologie erfordert kostengünstige und leicht implementierbare Lösungen für Entwickler und Enthusiasten. Dieses Projekt bietet eine einfache und effektive Möglichkeit, einen NFC-Reader zu erstellen und in eigene Projekte zu integrieren.

## Installation und Ausführung

### Voraussetzungen

- Raspberry Pi Pico W
- NFC-Modul (z.B. PN532)
- Jumper-Kabel
- Breadboard (optional)
- USB-Kabel zur Stromversorgung
- MicroPython Firmware auf dem Raspberry Pi Pico W

### Schritt-für-Schritt Anleitung

1. **MicroPython auf dem Raspberry Pi Pico W installieren**
   - Lade die neueste MicroPython Firmware von der [offiziellen Website](https://micropython.org/download/) herunter.
   - Flashe die Firmware auf den Pico W gemäß der [Anleitung](https://docs.micropython.org/en/latest/rp2/quickref.html).

2. **Verbindungen herstellen**
   - Verbinde das NFC-Modul mit dem Raspberry Pi Pico W wie folgt:
     - SDA an GP0
     - SCL an GP1
     - VCC an 3.3V
     - GND an GND

3. **Benötigte Bibliotheken installieren**
   - Lade die `micropython-pn532` Bibliothek herunter und kopiere sie auf den Pico W.

4. **Code hochladen und ausführen**
   - Erstelle eine Datei `main.py` auf dem Pico W und füge den notwendigen Code hinzu (siehe Beispiel unten).

5. **Ausführung**
   - Schließe den Pico W an deinen Computer an und öffne eine serielle Konsole (z.B. PuTTY, Thonny).
   - Lade und führe das Programm `main.py` aus.

## Benutzeranleitung

### Nutzung

1. Stelle sicher, dass der NFC-Reader korrekt angeschlossen und mit Strom versorgt ist.
2. Öffne eine serielle Konsole, um die Ausgabe des NFC-Readers zu sehen.
3. Halte eine NFC-Karte oder ein NFC-Tag an das Modul, um die UID auszulesen.
4. Die UID der NFC-Karte wird in der Konsole angezeigt.



## Veröffentlichung

Teile dein Projekt auf deinen sozialen Medien und nutze die folgenden Hashtags:
- #assistivetechnology
- #assistheidi
- #inclusioninternational
- #accessibility
- #FHTW
- #changeourtomorrow


