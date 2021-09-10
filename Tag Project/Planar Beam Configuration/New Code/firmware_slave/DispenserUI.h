/**
 * Helper class to display the the dispenser's user interface
 */
#ifndef DispenserUI_h
#define DispenserUI_h

#include "Arduino.h"

class DispenserUI
{
  public:
    DispenserUI();
    void begin();
    void clearScreen();
    void displayProductInfo(String name, float cost, String text);
    void displaySaleInfo(float price, float weight_in_grams, float cups);
};

#endif
