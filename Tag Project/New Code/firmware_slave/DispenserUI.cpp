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
//#include <GxEPD2_3C.h>

#define MAX_DISPLAY_BUFFER_SIZE 800 // e.g. full height for 200x200

// Intialise display object
#define MAX_HEIGHT_BW(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))
GxEPD2_BW<GxEPD2_420, MAX_HEIGHT_BW(GxEPD2_420)> display(GxEPD2_420(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));

// Include necessary Fonts 
#include <Fonts/FreeSans12pt7b.h>
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
  display.setRotation(2);
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
  display.setFont(&FreeSansBold24pt7b);
  display.getTextBounds(name, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = (display.width() - tbw) + 40 ; // Organic Almonds
//  uint16_t x = ((display.width() - tbw)/2) + 30 ; // Fusilli Pasta
//  uint16_t x = (((display.width() - tbw) * 3) / 4 ); // Sugar
  uint16_t y = ((display.height() + tbh) / 6) + 25; 

  // Placement of product cost/weight boxes (Middle)
  String costString = "$" + String(cost);
  int16_t tbx2, tby2;
  uint16_t tbw2, tbh2;
  display.setFont(&FreeSansBold24pt7b);
  display.getTextBounds(costString, 0, 0, &tbx2, &tby2, &tbw2, &tbh2);
  uint16_t x2 = (display.width() - tbw2) / 4;
  uint16_t y2 = ((display.height() + tbh2) / 3) + 60;

  int16_t tbx3, tby3;
  uint16_t tbw3, tbh3;
  String weightString = " / 100 g";
  display.getTextBounds(weightString, 0, 0, &tbx3, &tby3, &tbw3, &tbh3);
  uint16_t x3 = x2 + tbw2 ;
  uint16_t y3 = y2;

  // Placement of helper text box (Bottom)
  int16_t tbx4, tby4;
  uint16_t tbw4, tbh4;
  display.setFont(&FreeSans12pt7b);
  display.getTextBounds(text, 0, 0, &tbx4, &tby4, &tbw4, &tbh4);
  uint16_t x4 = (display.width() - tbw4) / 2;
  uint16_t y4 = ((display.height() + tbh4) / 4)+ 160;
  
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
    display.setFont(&FreeSansOblique18pt7b);
    Serial.print("displayProductInfo L3: ");
    Serial.println(weightString);
    display.print(weightString);
    
    display.setCursor(x4, y4);
    display.setFont(&FreeSans12pt7b);
    Serial.print("displayProductInfo L4: ");
    Serial.println(text);
    display.print(text);
  }
  while (display.nextPage()); 
}

void DispenserUI::displaySaleInfo(float price, float weight, float cups)
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
