/**
   A simple sketch to test and demo the dispenser's current features
*/

#include "DispenserData.h"
#include "DispenserUI.h"
#include "Dispenser.h"
#include <Wire.h>

// Const
const int dispensingTimout = 10000; //in milliseconds

double weight; 
double in_weight;
double fin_weight;
double weight_in_grams;
double prevWeight = 0;
const int numReadings = 10;
double readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
double total = 0;                  // the running total
double average = 0;                // the average
Dispenser dp;

void setup()
{
  // Initialise dispenser
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
        // If one is detected, toggle LED, buzzer and display sale screen
        dp.buzz();
        dp.clearScreen();
        dp.showSaleScreen(0);
        Wire.begin(9);                // join i2c bus with address #8
        Wire.onReceive(initialweight);
        delay(1500);
        Wire.onReceive(finalweight);
        dp.ledOn();
        
       
        // Keep filling container until timout is reached
         unsigned long startTime = millis();
         while (millis() - startTime < dispensingTimout) {
          
            if (average > 15)
            {
              if(average > prevWeight )
              {
                 dp.showSaleScreen(average);
                 prevWeight = average;
              }
            }
          // Toggle motor depending on whether
          // button is pressed
          if (dp.isButtonPressed()) {
            startTime = millis();
            //Serial.println("Dispensing.");
            dp.motorOn(255);
           } else {
            dp.motorOff();
          }
        
       }

        // After timout, "stop dispensing",
        // and return to product screen
        dp.motorOff();
        dp.ledOff();
        dp.buzz();
   if (weight_in_grams > 15)
      {
        dp.showSaleScreen(weight_in_grams);
      }
        delay(5000);
        dp.clearScreen();
        dp.showProductScreen();
    }
}
void initialweight(int howmany) {
  
  String weightstring = "";
  while(Wire.available()) // loop through all but the last
  {
    char w = Wire.read(); // receive byte as a character
    weightstring = weightstring + w;
//    Serial.print(weightstring);         // print the character
  }
   in_weight = weightstring.toFloat(); // respond with message of 6 bytes // as expected by master
   prevWeight = weight; 
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
   weight_in_grams = fin_weight * 1000;
   // subtract the last reading:
           total = total - readings[readIndex];
          // read from the sensor:
          readings[readIndex] = weight_in_grams;
          // add the reading to the total:
          total = total + readings[readIndex];
          // advance to the next position in the array:
          readIndex = readIndex + 1;

          // if we're at the end of the array...
          if (readIndex >= numReadings) {
          // ...wrap around to the beginning:
           readIndex = 0;
          }
           
          // calculate the average:
         average = total / numReadings;
//          Serial.println("Final weight is:");
//          Serial.println(average);
          Serial.println("Previous weight is:");
          Serial.println(prevWeight);
}
