/**
 * Central class that operates the dispenser's data,
 * user interface, sensors and actuators.
 */
#ifndef TestHX711_h
#define TestHX711_h

#include "Arduino.h"

class TestHX711
{
  public:
    TestHX711();
    void begin(int DataPin, int ClockPin);
    void set_scale(float scaleFactor);
    void tare();
    void increment();
    int get_units();
  private:

};

#endif
