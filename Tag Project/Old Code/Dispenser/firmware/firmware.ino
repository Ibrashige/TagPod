/**
 * A simple sketch to test and demo the dispenser's current features
 */ 

#include "DispenserData.h"
#include "DispenserUI.h"
#include "Dispenser.h"

Dispenser dp;

void setup() 
{
  Serial.begin(115200);
  // Initialise dispenser
  dp.begin();
  // Show product screen at startup
  dp.clearScreen();
  dp.showProductScreen();
}

void loop() 
{
  // Continuosly check for rfid cards
  if (dp.isCardPresent()) {
    // If one is detected, toggle LED
    // and display sale screen
    dp.ledOn();
    dp.clearScreen();
    int prevWeight = 0;
    dp.showSaleScreen(0);
    // Keep updating screen until 500 g us reached
    while (dp.getWeight() < 500) {
      int weight = dp.getWeight();
      if (weight > prevWeight) {
        dp.showSaleScreen(weight);
        prevWeight = weight;
      }
      // Toggle motor depending on whether
      // button is pressed
      if (dp.isButtonPressed()) {
        dp.motorOn(255);
      } else {
        dp.motorOff();
      }
    }
    // After 500 g, "stop dispensing", 
    // and return to product screen
    dp.motorOff();
    dp.showSaleScreen(dp.getWeight());
    dp.ledOff();
    delay(2500);
    dp.clearScreen();
    dp.showProductScreen();
  }
}
