/**
   A simple sketch to test and demo the dispenser's current features
*/

#include "DispenserData.h"
#include "DispenserUI.h"
#include "Dispenser.h"
#include <Wire.h>
//#include <WiFi.h>
//#include <HTTPClient.h>

// Const
const int dispensingTimout = 5000; //in milliseconds
float weight; 
float prevWeight = 0;

// Wifi constants
//const char* wifiSsid = "Crunchy";
//const char* wifiPassword = "muffin4me";
//const int httpConnectionTimeout = 500;
//const char* cartServiceURL = "http://10.0.0.88:8080/Cart";
//const char* pulseServiceURL = "http://10.0.0.88:8080/Pulse";

Dispenser dp;

void setup()
{
  // Initialise dispenser

  // Connect to WiFi
//  WiFi.begin(wifiSsid, wifiPassword);

//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.println("Connecting to WiFi...");
//  }

//  Serial.println("Connected to WiFi...");
//  Serial.println(WiFi.localIP());

  dp.begin();
  // Show product screen at startup
  dp.clearScreen();
  dp.showProductScreen();
  Serial.begin(115200);
}

void loop()
{
      // Continuosly check for rfid cards
      if (dp.isCardPresent()) {
        Serial.print("CardID: ");
        Serial.println(dp.getCardID());
        // If one is detected, toggle LED
        // and display sale screen
        dp.buzz();
        dp.clearScreen();
        dp.showSaleScreen(0);
        dp.ledOn();

        
        // Keep filling container until timout is reached
         unsigned long startTime = millis();
         while (millis() - startTime < dispensingTimout) {
            Wire.begin(8);                // join i2c bus with address #8
            Wire.onReceive(receiveEvent);
             
          // Toggle motor depending on whether
          // button is pressed
          if (dp.isButtonPressed()) {
            startTime = millis();
            Serial.println("Dispensing.");
            dp.motorOn(255);
//            Wire.onReceive(receiveEvent);
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
        //dp.showSaleScreen(weight);
        dp.ledOff();
//        Wire.onReceive(receiveEvent);
        //dp.resetWeight(); //reset
        dp.clearScreen();
        dp.showProductScreen();
    }
      delay(2500);
//      weight = 0;
//      prevWeight = 0;
}
void receiveEvent(int howmany) {
  
  String weightstring = "";
  while(Wire.available()) // loop through all but the last
  {
    char w = Wire.read(); // receive byte as a character
    weightstring = weightstring + w;
    //Serial.print(weightstring);         // print the character
  }
   weight = weightstring.toFloat(); // respond with message of 6 bytes // as expected by master
   //Serial.println(weight);
   //if (weight < prevWeight) {
      dp.showSaleScreen(weight);
      prevWeight = weight; 
   // }
//    Serial.println(weight);
    Serial.println(prevWeight);
}
