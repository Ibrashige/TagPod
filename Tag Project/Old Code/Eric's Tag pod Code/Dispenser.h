/**
 * Central class that operates the dispenser's data,
 * user interface, sensors and actuators.
 */
#ifndef Dispenser_h
#define Dispenser_h

#include "Arduino.h"

class Dispenser
{
  public:
    Dispenser();
    void begin();
    // Button
    bool isButtonPressed();
    // LED
    void ledOn();
    void ledOff();
    // Buzzer
    void buzz();
    // RFID Module
    bool isCardPresent();
    String getCardID();
    // DC Motor
    void motorOn(byte power);
    void motorOff();
    // Load Cell (scale)
    unsigned int getWeight();
    // Display
    void clearScreen();
    void showProductScreen();
    void showSaleScreen(unsigned int weight);
    // Miscellaneous
    void updateProductInfo(
      float cost,
      String name,
      String text,
      unsigned int density
    );
    void addWeight();
    void resetWeight();
  private:

};

#endif
