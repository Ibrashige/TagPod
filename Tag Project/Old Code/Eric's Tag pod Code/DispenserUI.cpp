/**
 * Helper class to display the the dispenser's user interface
 * on the Waveshare 2.9 inch e-paper module (black/white)
 * 
 * Relies on the GxEPD2 e-paper display found at https://github.com/ZinggJM/GxEPD2
 * The pin mapping is as follows:
 * BUSY -> 4, RST -> 16, DC -> 17, CS -> SS(5), CLK -> SCK(18), DIN -> MOSI(23), GND -> GND, 3.3V -> 3.3V
 *
 * More info on how displays work here:
 * https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
 */
#include "Arduino.h"
#include "DispenserUI.h"

// Include display library
#include <GxEPD2_BW.h>

// Intialise display object
GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));

// Include necessary Fonts 
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSansOblique12pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <Fonts/FreeSansBoldOblique24pt7b.h>

DispenserUI::DispenserUI()
{
 
}

void DispenserUI::begin()
{
  // Initialises default settings.
  display.init(115200);
  display.setRotation(1);
  display.setTextColor(GxEPD_BLACK);
  display.setPartialWindow(0,0, display.width(), display.height());
}

void DispenserUI::clearScreen()
{
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
  }
  while (display.nextPage ());
  display.setPartialWindow(0,0, display.width(), display.height());  
}

void DispenserUI::displayProductInfo(String name, float cost, String text)
{
  // Placement of product name box (Top)
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.setFont(&FreeSansBold18pt7b);
  display.getTextBounds(name, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = (display.width() - tbw) / 2;
  uint16_t y = (display.height() + tbh) / 4;

  // Placement of product cost/weight boxes (Middle)
  String costString = "$" + String(cost);
  int16_t tbx2, tby2;
  uint16_t tbw2, tbh2;
  display.setFont(&FreeSansBold24pt7b);
  display.getTextBounds(costString, 0, 0, &tbx2, &tby2, &tbw2, &tbh2);
  uint16_t x2 = (display.width() - tbw2) / 4;
  uint16_t y2 = ((display.height() + tbh2) / 3) + 30;

  String weightString = " / 100 g";
  uint16_t x3 = x2 + tbw2 + 5;
  uint16_t y3 = y2;

  // Placement of helper text box (Bottom)
  int16_t tbx4, tby4;
  uint16_t tbw4, tbh4;
  display.setFont(&FreeSans9pt7b);
  display.getTextBounds(text, 0, 0, &tbx4, &tby4, &tbw4, &tbh4);
  uint16_t x4 = (display.width() - tbw4) / 2;
  uint16_t y4 = ((display.height() + tbh4) / 4) + 80;
  
  // Display the boxes on the screen
  display.firstPage();
  do
  {
    display.setCursor(x, y);
    display.setFont(&FreeSansBold18pt7b);
    Serial.print("displayProductInfo L1: ");
    Serial.println(name);
    display.print(name);
    
    display.setCursor(x2, y2);
    display.setFont(&FreeSansBoldOblique24pt7b);
    Serial.print("displayProductInfo L2: ");
    Serial.println(costString);
    display.print(costString);
 
    display.setCursor(x3, y3);
    display.setFont(&FreeSansOblique12pt7b);
    Serial.print("displayProductInfo L3: ");
    Serial.println(weightString);
    display.print(weightString);
    
    display.setCursor(x4, y4);
    display.setFont(&FreeSans9pt7b);
    Serial.print("displayProductInfo L4: ");
    Serial.println(text);
    display.print(text);
  }
  while (display.nextPage()); 
}

void DispenserUI::displaySaleInfo(float price, unsigned int weight, float cups)
{
  // Placement of price box (Top)
  String priceString = "$" + String(price);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.setFont(&FreeSansBold24pt7b);
  display.getTextBounds(priceString, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = (int) (display.width() - tbw) / 2;
  uint16_t y = (int) (display.height() + tbh) / 3;

  // Placement of amount box (Bottom)
  String amtString = String(weight) + " g  " + String(cups) + " cup"; 
  int16_t tbx2, tby2;
  uint16_t tbw2, tbh2;
  display.setFont(&FreeSansOblique18pt7b);
  display.getTextBounds(amtString, 0, 0, &tbx2, &tby2, &tbw2, &tbh2);
  uint16_t x2 = (int) (display.width() - tbw2) / 2;
  uint16_t y2 = (int) (display.height() + tbh2) / 3 * 2;

  // Display the boxes on the screen
  display.firstPage();
  do
  {
    display.setCursor(x, y);
    display.setFont(&FreeSansBoldOblique24pt7b);
    display.print(priceString);
    Serial.print("displaySaleInfo L1: ");
    Serial.println(priceString);

    display.setCursor(x2, y2);
    display.setFont(&FreeSansOblique18pt7b);
    Serial.print("displaySaleInfo L2: ");
    Serial.println(amtString);
    display.print(amtString);
  }
  while (display.nextPage()); 
}
