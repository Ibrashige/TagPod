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
#include "DispenserData.h"
#include "DispenserUI.h"
#include "Dispenser.h"
//#include "HX711.h" // For Testing only
#include "TestHX711.h"
#include "MFRC522.h"


// Pin Definitions
const int buttonPin = 34;
const int ledPin = 15;
const int buzzerPin = 0;
const int buzzerFrequency = 600;
const int buzzerChannel = 0;
const int rfidSS = 21;
const int spiRST = 22;
const int motorPin1 = 33;
const int motorPin2 = 32;
const int motorEnablePin = 2;
const int motorFrequency = 30000;
const int motorChannel = 1;
const int loadCellDataPin = 26;
const int loadCellClockPin = 25;
const int pwmResolution = 8; // in bits

// Declare load cell object
TestHX711 scale;

// Initialise RFID module
MFRC522 rfid(rfidSS, spiRST);

// Declare dispenser UI and Data objects
const bool isDebugMode = false;
DispenserUI UI;    
DispenserData data; 

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
  
  // Pushbutton setup
  Serial.println("Configuring Push Button");
  pinMode(buttonPin, INPUT);
  
  // LED setup
  Serial.println("Configuring LED");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Buzzer setup
  Serial.println("Configuring Buzzer");
  ledcSetup(buzzerChannel, buzzerFrequency, pwmResolution);
  ledcAttachPin(buzzerPin, buzzerChannel);
  
  // RFID setup
  Serial.println("Starting RFID");
  rfid.PCD_Init();
  delay(500);
  Serial.println("Starting RFID - Complete");
  
  // Motor and Motor Shield setup
  Serial.println("Configuring Motor Shield");
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorEnablePin, OUTPUT);
  ledcSetup(motorChannel, motorFrequency, pwmResolution);
  ledcAttachPin(motorEnablePin, motorChannel);
  
  // Load cell setup
  Serial.println("Configuring Load Cell");
  scale.begin(loadCellDataPin, loadCellClockPin);
  scale.set_scale(451.f);
  scale.tare();
  
  // Display setup
  Serial.println("Configuring Display");
  UI.begin();

  Serial.println("Dispenser Initialization - Complete");
}

bool Dispenser::isButtonPressed()
{
  bool returnVal = digitalRead(buttonPin) == HIGH;
  if(isDebugMode) {
    Serial.print("Dispenser::isButtonPressed: ");
    Serial.println(returnVal);
  }
  return returnVal;
}

void Dispenser::ledOn()
{
  digitalWrite(ledPin, HIGH);
}

void Dispenser::ledOff()
{
  digitalWrite(ledPin, LOW);
}

void Dispenser::buzz()
{
  ledcWriteTone(buzzerChannel, buzzerFrequency);
  delay(300);  // Default buzz time
  ledcWrite(buzzerChannel, -1);
}

bool Dispenser::isCardPresent()
{
  bool returnVal = true;
  
  if (!rfid.PICC_IsNewCardPresent()) {
    returnVal = false;
  } else if (!rfid.PICC_ReadCardSerial()) {
    returnVal = false;
  }

  if(isDebugMode) {
    Serial.print("Dispenser::isCardPresent: ");
    Serial.println(returnVal);
  }
  
  return returnVal;
}

String Dispenser::getCardID()
{
  // Read card UID
  // (Can probably be done more efficiently
  //  using char* instead of String Objects)
  String ID = "";
  for (int i = 0; i < rfid.uid.size; i++) {
   if (rfid.uid.uidByte[i] < 0x10) {ID += "0";}
   ID += String(rfid.uid.uidByte[i], HEX);
  }
  // Stop the reading process and return the UID
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  return ID; 
}

void Dispenser::motorOn(byte power)
{
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  ledcWrite(motorChannel, power);
}

void Dispenser::motorOff()
{
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  ledcWrite(motorChannel, 0);
}

unsigned int Dispenser::getWeight()
{
  // Prevents load cell from returning
  // slightly negative weights
  if (scale.get_units() <= 0) {
    return 0;
  }
  // Return weight rounded to the nearest gram
  return round(scale.get_units());
}

void Dispenser::clearScreen()
{
  UI.clearScreen();
}

void Dispenser::showProductScreen()
{  
  UI.displayProductInfo(
    data.getProductName(),
    data.getProductCost(),
    data.getHelperText()
  );
}

void Dispenser::showSaleScreen(unsigned int weight)
{
  UI.displaySaleInfo(
    data.weightToPrice(weight),
    weight,
    data.weightToCups(weight)
  );
}

void Dispenser::updateProductInfo(float cost, String name, String text, unsigned int density)
{
  data.setProductCost(cost);
  data.setProductName(name);
  data.setHelperText(text);
  data.setProductDensity(density);
}

// To add weight from fake TestHX711
void Dispenser::addWeight(){
  scale.increment();
}

// To add weight from fake TestHX711
void Dispenser::resetWeight(){
  scale.tare();
}
