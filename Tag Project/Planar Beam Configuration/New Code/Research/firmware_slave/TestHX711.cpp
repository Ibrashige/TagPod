#include "Arduino.h"
#include "TestHX711.h"

int scaleValue;
int incrementValue;
float scalingFactor;

TestHX711::TestHX711(){
  scaleValue = 0;
  scalingFactor = 1.f;
  incrementValue = 1;
}

void TestHX711::begin(int DataPin, int ClockPin){
}

void TestHX711::set_scale(float scaleFactor){
  scalingFactor = scaleFactor;
}

void TestHX711::tare(){
  scaleValue = 0;
}

int TestHX711::get_units(){
  return scaleValue * scalingFactor;
}

void TestHX711::increment(){
  scaleValue += incrementValue;
}
