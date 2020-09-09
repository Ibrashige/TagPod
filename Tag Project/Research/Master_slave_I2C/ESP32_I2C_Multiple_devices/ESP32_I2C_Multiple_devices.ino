/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-i2c-communication-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <Wire.h>

void setup() {
  
  Wire.begin();
  Serial.begin(115200);
 
}

void loop() {
   Wire.requestFrom(8, 16);    // request 16 bytes from slave device #8
  //Wire.requestFrom(9, 6);
  //Wire.requestFrom(7, 6);
  
  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.println(c);         // print the character
  }
  delay(1000);
}
