# Firmware

This repository contains all the logic associated with controlling the Dispenser's sensors, actuators, and behavior.

## Prerequisites

The following libraries must be installed on your computer for the code to compile:
1. HX711 for the load cell: <https://github.com/bogde/HX711>
2. MFRC522 for the RFID module: <https://github.com/miguelbalboa/rfid>
3. GxEPD2 for the e-paper display: <https://github.com/ZinggJM/GxEPD2>

*You must add the ESP32 board to your IDE. The instructions for doing so on the Arduino IDE can be found [here](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/).*

## Installation

Simply flash ```firmware.ino``` to the ESP32 using the Arduino IDE or your editor of preference. You may need to hold the boot button down during the upload process.

## Usage 

1. Approximate a compatible RFID fob/card to the reader.
2. The product info screen should switch to the sale screen.
3. Add weights to the scale and watch the price update.
4. The program switches back to the product screeen after a certain maximum weight.

## Parts & Wiring

The following electronic parts are used Dispenser: ```ESP32 Devkit-C```, ```Waveshare 2.9 in Black/White E-Paper Display```, ```HX711 load cell```,```MFRC522 RFID Module```, ```L298N  H-Bridge Motor Driver```, ```12V DC Motor```, ```LED Pushbutton```, strain gauge, buzzer, etc... Their wiring is described below.

### E-Paper Display
```
BUSY -> 4
RST  -> 16
DC   -> 17
CS   -> 5
CLK  -> 18
DIN  -> 23
GND  -> GND
VCC  -> 3.3V
```
### RFID Module
```
SDA  -> 21
SCK  -> 18
MOSI -> 23
MISO -> 19
RST  -> 22
3.3V -> 3.3V 
GND  -> GND
```
*MOSI/SCK and CLK/DIN lines are shared between the display and RFID module.*

### Load Cell
``` 
VCC -> 3.3V
VDD -> 3.3V
DAT -> 26
CLK -> 25
GND -> GND

RED  -> RED (strain gauge)
BLK  -> BLK (strain gauge)
WHT  -> WHT (strain gauge)
YLW  -> YLW (strain gauge)
```
*VCC and VDD are grouped*.

### Motor Driver
```
ENA  -> 2
IN1  -> 33
IN2  -> 32
OUT1 -> + side of motor
OUT2 -> - side of motor
VCC  -> 12V from power supply
GND  -> ESP32 GND ansd power supply GND
5V   -> 5V on ESP32
```

### Button
```
GND -> 10K ohm resistor -> pin 34 -> 5V
```
### LED
``` 
GND -> LED -> 220 ohm -> pin 0
```
### Buzzer
``` 
GND  -> buzzer -> 100 ohm -> pin 2
```

## Known Bugs
1. Using the buzzer with other parts (particularly the display) in the same sketch causes the program to freeze. (Investigate the pin used for the buzzer and what effects it may have on other pins)


2. Everytime the display is updated, the led flickers. (Investigate the relevant pins/wiring).

## To-Do 
1. Add logic to connect  to wi-fi and integrate with Google Cloud IoT Core.
2. Add logic to easily configure Wi-Fi credentials.
3. Current scale logic is for testing purposes (weight is added rather than being subracted), modify it for real-world use.