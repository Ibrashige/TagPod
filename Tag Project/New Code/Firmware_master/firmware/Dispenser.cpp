/**
 * Central class that operates the dispenser's data,
 * user interface, sensors and actuators.
 * 
 * Relies on the following libraries:
 * HX711 for the load cell: https://github.com/bogde/HX711
 *  - Check README for calibration details
 * MFRC522 for the rfid module: https://github.com/miguelbalboa/rfid
 */
#include "Arduino.h"
#include "SPI.h"
#include "Dispenser.h"
#include "MFRC522.h"


// Pin Definitions
//const float offset = 14.40; // offset for the load cell to indicate 0 load at 2.5 V
const float offset = 0.05; // offset for the load cell to indicate 0 load at 2.5 V
const int VOUT = 32;
const int pwmResolution = 8; // in bits
const float vpp = 0.00122070312; // 5V/4096 for ADC conversion
const float totalLoad = 22.68; // maximum load capacity 12.5 pounds
const float a = 1100; // Amplifier Gain
const float s = 0.0008998; // load cell sensitivity 
const float ve = 4.97; //Excitation voltage
float points;
float voltage;
float load;
float numerator; // numerator of load calculation
float voutmax; // denominator of load calculation


// Declare dispenser UI and Data objects
const bool isDebugMode = false;


Dispenser::Dispenser()
{
  
}

void Dispenser::begin()
{
  Serial.println("Dispenser Initialization - Started");
  
  // Init SPI communication
  Serial.println("Starting SPI");
  SPI.begin();
  Serial.println("Starting SPI, Complete");
  
//  // RFID setup
//  Serial.println("Starting RFID");
//  rfid.PCD_Init();
//  delay(500);
//  Serial.println("Starting RFID - Complete");
  
  // Load cell setup
  Serial.println("Configuring Load Cell");
//  scale.begin(loadCellDataPin, loadCellClockPin);
//  scale.set_scale(451.f);
//  scale.tare();
  
  Serial.println("Dispenser Initialization - Complete");
}


char Dispenser::getCardID()
{
  char c;
  // Read card UID
  Wire.requestFrom(8,11);    // request 16 bytes from slave device #8
  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
      //Serial.println("Card ID: ");
      Serial.print(c);         // print the character
  }
  //Serial.println();
 
}
float Dispenser::getWeight()
{
  float reading = analogRead(32); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
  if(reading < 1 || reading > 4095) return 0;
  // return -0.000000000009824 * pow(reading,3) + 0.000000016557283 * pow(reading,2) + 0.000854596860691 * reading + 0.065440348345433;
  float volt = (-0.000000000000016 * pow(reading,4) + 0.000000000118171 * pow(reading,3)- 0.000000301211691 * pow(reading,2)+ 0.001109019271794 * reading + 0.034143524634089)-0.15;
  voltage = volt * (1.51515151515);
  numerator = totalLoad * (voltage);
  voutmax = s * a * ve;              // raw output voltage to its maximum rated capacity
  float load = numerator/voutmax  ; // weight in kgs 
  // Prevents load cell from returning
  // slightly negative weights
  if (load <= 0) {
    return 0;
  }
  // Return weight rounded to the nearest kilogram
  return load;
}


// To add weight from fake TestHX711
//void Dispenser::addWeight(){
//  scale.increment();
//}
//
//// To add weight from fake TestHX711
//void Dispenser::resetWeight(){
//  scale.tare();
//}
