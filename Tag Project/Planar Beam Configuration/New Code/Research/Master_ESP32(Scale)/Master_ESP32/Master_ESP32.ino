// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

//**
// * Central class that operates the dispenser's data, sensors and actuators.
// * 
// * Relies on the tacuna systems knowledge base:
// https://tacunasystems.com/knowledge-base/load-cell-faq/
// *
// *
// */
 
const float offset = 4.1056; // offset for the load cell to indicate 0 load at 2.5 V
const float vpp = 0.00122070312; // 5V/4096 for ADC conversion
const float totalLoad = 22.68; // maximum load capacity 12.5 pounds
const float a = 1100; // Amplifier Gain
const float s = 0.0008998; // load cell sensitivity 
const float ve = 4.97; //Excitation voltage
float points;
float voltage;
float load;
float numerator; // numerator of load calculation
float voutmax; // denominator of load calculation


#define VOUT  32
#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  Serial.println("Weighing code");
}


void loop() {
    calculatevoltage();
    calculateweight();

    int x = load;
    Wire.beginTransmission(8);
    Wire.write("Weight in Kg: ");
    Wire.write(x);
    Wire.endTransmission();

    x++;
//    Wire.requestFrom(8,11);    // request 16 bytes from slave device #8
  //Wire.requestFrom(9, 6);
  //Wire.requestFrom(7, 6);
//  
//  while (Wire.available()) { // slave may send less than requested
//    char c = Wire.read(); // receive a byte as character
//   
//      Serial.print(c);         // print the character
//  }

  Serial.println();
  delay(5000);
}
float calculatevoltage(){
  
  points = (float)analogRead(VOUT); 
  voltage = (points / 4095 * 4.9995) ; 
  Serial.print("calculated voltage is:");
  Serial.println(voltage);

}

void calculateweight(){
  numerator = totalLoad * (voltage);
  voutmax = s * a * ve;              // raw output voltage to its maximum rated capacity
  load = numerator/voutmax ; // weight in kgs

 if(load >= 0 && load <= 0.05 )
 {
    load = 0;
 }
  Serial.print("calculated weight in kilograms is:");
  Serial.println(load); 
  
}
