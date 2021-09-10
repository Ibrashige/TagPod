/**
 * Central class that operates the dispenser's data,
 * user interface, sensors and actuators.
 */
#ifndef Dispenser_h
#define Dispenser_h

#include "Arduino.h"
#include <Wire.h>

class Dispenser
{
  public:
    Dispenser();
    void begin();
    // RFID Module
    bool isCardPresent();
    char getCardID();
    // Load Cell (scale)
    float getWeight();
    void addWeight();
    void resetWeight();
  private:

};

#endif
