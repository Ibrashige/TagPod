/**
   A simple sketch to test and demo the dispenser's current features
*/

#include "DispenserData.h"
#include "DispenserUI.h"
#include "Dispenser.h"
#include <Wire.h>

// Const
const int dispensingTimout = 5000; //in milliseconds
const int numReadings = 10;

float readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

float weight; 
float in_weight;
float fin_weight;
float prevWeight = 0;

Dispenser dp;

void setup()
{
  // Initialise dispenser
  dp.begin();
  // Show product screen at startup
  dp.clearScreen();
  dp.showProductScreen();
  Serial.begin(115200);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop()
{
      // Continuosly check for rfid cards
      if (dp.isCardPresent()) {
        Serial.print("CardID: ");
        Serial.println(dp.getCardID());
        // If one is detected, toggle LED, buzzer and display sale screen
        dp.buzz();
        dp.clearScreen();
        dp.showSaleScreen(0);
        Wire.begin(9);                // join i2c bus with address #8
        Wire.onReceive(initialweight);
        delay(2000);
        dp.ledOn();
        Wire.onReceive(finalweight);
       
        // Keep filling container until timout is reached
         unsigned long startTime = millis();
         while (millis() - startTime < dispensingTimout) {   
         dp.showSaleScreen(fin_weight);
          // Toggle motor depending on whether
          // button is pressed
          if (dp.isButtonPressed()) {
            startTime = millis();
          //  Serial.println("Dispensing.");
            dp.motorOn(255);
           } else {
            dp.motorOff();
          }
       
          delay(500);
       }

        // Debug echo
//        Serial.println("Exiting dispensing mode.");
//        Serial.print("CardID: ");
//        Serial.println(cardID);
//        Serial.print("machineID: ");
//        Serial.println(machineID);
//        Serial.print("weightGrams: ");
//        Serial.println(weightGrams);

        // After timout, "stop dispensing",
        // and return to product screen
        dp.motorOff();
        dp.ledOff();
        dp.showSaleScreen(fin_weight);
        delay(2000);
        dp.clearScreen();
        dp.showProductScreen();
    }
      delay(2500);
//      weight = 0;
//      prevWeight = 0;
}
void initialweight(int howmany) {
  
  String weightstring = "";
  while(Wire.available()) // loop through all but the last
  {
    char w = Wire.read(); // receive byte as a character
    weightstring = weightstring + w;
    Serial.print(weightstring);         // print the character
  }
   in_weight = weightstring.toFloat(); // respond with message of 6 bytes // as expected by master
   //Serial.println(weight);
   //if (weight < prevWeight) {
      prevWeight = weight; 
   // }
//    Serial.println(weight);
    //Serial.println("Initial weight is:");
    Serial.println(in_weight);
}

void finalweight(int howmany) {
  
  String weightstring = "";
  while(Wire.available()) // loop through all but the last
  {
    char w = Wire.read(); // receive byte as a character
    weightstring = weightstring + w;
    //Serial.print(weightstring);         // print the character
  }
   weight = weightstring.toFloat(); // respond with message of 6 bytes // as expected by master
   fin_weight = in_weight - weight;
   //Serial.println(weight);
//    Serial.println(weight);
 // else{
        Serial.println("Final weight is:");
        Serial.println(fin_weight);
   //}
}
