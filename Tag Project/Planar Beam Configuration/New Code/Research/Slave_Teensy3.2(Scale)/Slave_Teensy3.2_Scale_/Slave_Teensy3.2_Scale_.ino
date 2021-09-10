   // Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Wire.h>
//#include <SPI.h>
//#include <MFRC522.h>
//#define SS_PIN 10
//#define RST_PIN 9
//MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

//String UID;
//char ID[50];

void setup() {
//  SPI.begin();      // Initiate  SPI bus
//  mfrc522.PCD_Init();   // Initiate MFRC522
//  Serial.println("Approximate your card to the reader...");
  Serial.println();
//  Wire.onRequest(requestEvent);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);   // Initiate a serial communication
 // register event
}

void loop() {
//  findrfid();
  delay(100);
}

//void findrfid(){
//   // Look for new cards
//  if ( ! mfrc522.PICC_IsNewCardPresent()) 
//  {
//    return;
//  }
//  // Select one of the cards
//  if ( ! mfrc522.PICC_ReadCardSerial()) 
//  {
//    return;
//  }
//  //Show UID on serial monitor
//  Serial.print("UID tag :");
//  String content= "";
//  byte letter;
//  for (byte i = 0; i < mfrc522.uid.size; i++) 
//  {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
//     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
//     content.concat(String(mfrc522.uid.uidByte[i], HEX));
//  }
//  Serial.println();
//  content.toUpperCase();
//  UID = content.substring(1);
//  UID.toCharArray(ID,15);
//  mfrc522.PICC_HaltA();
//}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()

//void requestEvent() {
//  
//   Wire.write(ID); // respond with message of 6 bytes // as expected by master
//   Wire.write("\n");
//
//}
void receiveEvent(int howmany) {
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
   int x = Wire.read(); // respond with message of 6 bytes // as expected by master
   Serial.println(x);

}
