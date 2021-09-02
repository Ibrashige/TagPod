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

## Other Useful Resources
1. Load cell & Amplifier FAQs: <https://tacunasystems.com/knowledge-base/load-cell-faq/>
2. Specifications Relating to Non-automatic Weighing Devices (1998): <https://laws-lois.justice.gc.ca/eng/regulations/SI-98-81/page-1.html#h-653180>
3. DATAQ Instruments ADC resolution Calculation: <https://www.dataq.com/data-acquisition/general-education-tutorials/how-much-adc-resolution-do-you-really-need.html>

## Installation

Simply flash ```firmware.ino``` to the ESP32 using the Arduino IDE or your editor of preference. You may need to hold the boot button down during the upload process.

## Usage 

1. Approximate a compatible RFID fob/card to the reader.
2. The product info screen should switch to the sale screen.
3. Push the dispenser button and add dispensed weight to the scale while monitoring the price update.
4. The program switches back to the product screen after a certain maximum weight.

## FlowChart
![Image of Flowchart](https://github.com/Ibrashige/TagPod/blob/master/Tag%20Project%20flowchart.png)

## Connections
![Image of Flowchart](https://github.com/Ibrashige/TagPod/blob/master/Tag%20Project%20(1).png)

## Parts & Wiring

The following electronic parts are used Dispenser: ```ESP32 Devkit-C```,```Teensy USB Board, Version 3.2```,```Waveshare 4.2 in Black/White/Red E-Paper Display```, ```EMBSGB200C Tacuna Systems amplifier```,```ANYLOAD 23KG capacity load cells/w junction box```,```MFRC522 RFID Module```, ```VNH5019 Motor Driver Carrier```, ```150:1 Metal Gearmotor 37Dx57L mm 12V (Helical Pinion)```, ```LED Pushbutton```, buzzer, etc... Their wiring is described below.

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
SDA  -> 15
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
VOUT -> Voltage Divider (R1 = 100K Ohm R2 = 200K Ohm) -> 36 (Sensor VP)
GND -> GND

```
*VCC and VDD are grouped*.

### Motor Driver (To designated Teensy 3.2)
```
Motor PWM -> 23
Motor Pin 1 -> 2
Motor Pin 2 -> 3
VCC  -> 12V from power supply
GND  -> Teensy 3.2 GND and power supply GND
5V   -> 5V on Teensy 3.2
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
## I2C Wiring
```
ESP32: 
SCL -> pin 22
SDA -> pin 21
```
```
Teensy 3.2:
SCL -> pin 19 (A5)
SDA -> pin 18 (A4)
```
*SCL and SDA lines are shared between each MCU (i.e connect ESP32's pin 22 to Teensy 3.2's pin 19 and so on).*

## Known Bugs
1. Display updates when the weight is not changed due to the initial zero setting mechanism (IZSM) being configured over entire capacity, set weight and other variables to zero on sale screen

2. Everytime the display is updated while dispensing, the pushbutton switch lags the motor and a performance latency is introduced when dispensing. (Investigate the relevant pins/wiring).

3. Scale is off by -0.5 kg due to inadequate weight/load monitoring. Find a way to reduce deviance between theoretical and actual value.

## To-Do 
1. Add logic to connect  to wi-fi and integrate with Google Cloud IoT Core.
2. Add logic to easily configure Wi-Fi credentials.

