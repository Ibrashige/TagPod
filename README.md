# Firmware

This repository contains all the logic associated with controlling the Dispenser's sensors, actuators, and behavior.

## Prerequisites

The following libraries must be installed on your computer for the code to compile:
1. Arduino AVR boards library (For Teensy 3.2)
2. ESP32 Arduino library: <https://github.com/espressif/arduino-esp32> 
2. MFRC522 for the RFID module: <https://github.com/miguelbalboa/rfid>
3. GxEPD2 for the e-paper display: <https://github.com/ZinggJM/GxEPD2>
4. HX711 for the load cell: <https://github.com/bogde/HX711>

*You must add the ESP32 board to your IDE. The instructions for doing so on the Arduino IDE can be found [here](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/).*

## Installation

Simply flash ```firmware.ino``` to the ESP32 using the Arduino IDE or your editor of preference. You may need to hold the boot button down during the upload process.

## Usage 

1. Approximate a compatible RFID fob/card to the reader.
2. The product info screen should switch to the sale screen.
3. Add weights to the scale and watch the price update.
4. The program switches back to the product screeen after a certain maximum weight.

## Parts & Wiring

The following electronic parts are used Dispenser: ```ESP32 Devkit-C```,```Teensy USB Board, Version 3.2```,```Waveshare 4.2 in Black/White/Red E-Paper Display```, ```EMBSGB200C Tacuna Systems amplifier```,```ANYLOAD 23KG capacity load cells/w junction box```,```MFRC522 RFID Module```, ```TB67S249FTG Stepper Motor Driver Carrier - Full Breakout```, ```12V DC Motor```, ```LED Pushbutton```, buzzer, etc... Their wiring is described below.

### E-Paper Display (To designated Teensy 3.2)
```
BUSY -> 7
RST  -> 9
DC   -> 8
CS   -> 10
CLK  -> 13
DIN  -> 11
GND  -> GND
VCC  -> 3.3V
```
### RFID Module (To designated Teensy 3.2)
```
SDA  -> 18
SCK  -> 13
MOSI -> 11
MISO -> 12
RST  -> 6
3.3V -> 3.3V 
GND  -> GND
```
*MOSI/SCK and CLK/DIN lines are shared between the display and RFID module.*

### EMBSGB200C Load Cell Amplifier (To ESP32)
``` 
VIN+ -> 12V
VOUT -> Voltage Divider (R1 = 1K Ohm R2 = 2K Ohm) -> 32
GND -> GND

```
*VCC and VDD are grouped*.

### Motor Driver (To designated Teensy 3.2)
```
(DIR)CW/CCW -> 23
(STEP)CLK -> 22
VCC  -> 12V from power supply
GND  -> ESP32 GND ansd power supply GND
5V   -> 5V on ESP32
```

### Button (To designated Teensy 3.2)
```
JST 1: 5V (From Pololu D24V50F5 5V regulator)
JST 2: pin 5 -> 10K ohm resistor -> GND 
```
### LED (To designated Teensy 3.2)
``` 
JST 1 (Anode)[+]: 220 ohm resistor -> pin 4
JST 2 (Cathode)[-]: GND
```
### Buzzer (To designated Teensy 3.2)
``` 
GND  -> 100 ohm -> buzzer ->  pin 21
```

## Known Bugs
1. Using the buzzer with other parts (particularly the display) in the same sketch causes the program to freeze. (Investigate the pin used for the buzzer and what effects it may have on other pins)


2. Everytime the display is updated, the led flickers. (Investigate the relevant pins/wiring).

## To-Do 
1. Add logic to connect  to wi-fi and integrate with Google Cloud IoT Core.
2. Add logic to easily configure Wi-Fi credentials.
3. Current scale logic is for testing purposes (weight is added rather than being subracted), modify it for real-world use.
