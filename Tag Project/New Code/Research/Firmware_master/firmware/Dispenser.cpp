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
const float offset = 14.40; // offset for the load cell to indicate 0 load at 2.5 V
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

//bool Dispenser::isCardPresent()
//{
//  bool returnVal = true;
//  
//  if (!rfid.PICC_IsNewCardPresent()) {
//    returnVal = false;
//  } else if (!rfid.PICC_ReadCardSerial()) {
//    returnVal = false;
//  }
//
//  if(isDebugMode) {
//    Serial.print("Dispenser::isCardPresent: ");
//    Serial.println(returnVal);
//  }
//  
//  return returnVal;
//}

//String Dispenser::getCardID()
//{
//  // Read card UID
//  // (Can probably be done more efficiently
//  //  using char* instead of String Objects)
//  String ID = "";
//  for (int i = 0; i < rfid.uid.size; i++) {
//   if (rfid.uid.uidByte[i] < 0x10) {ID += "0";}
//   ID += String(rfid.uid.uidByte[i], HEX);
//  }
//  // Stop the reading process and return the UID
//  rfid.PICC_HaltA();
//  rfid.PCD_StopCrypto1();
//  return ID; 
//}
float Dispenser::getWeight()
{
  points = (float)analogRead(VOUT); 
  voltage = (points / 4095 * 4.9995) ;
  numerator = totalLoad * (voltage);
  voutmax = s * a * ve;              // raw output voltage to its maximum rated capacity
  float load = numerator/voutmax - offset ; // weight in kgs 
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
