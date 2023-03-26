/**
   A simple sketch to test and demo the dispenser's current features
*/

#include "Dispenser.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>

// Const
const int dispensingTimout = 5000; //in milliseconds
int prevWeight = 0;

// Wifi constantsskb
const char* wifiSsid = "Crunchy";
const char* wifiPassword = "muffin4me";
const int httpConnectionTimeout = 500;
const char* cartServiceURL = "http://10.0.0.88:8080/Cart";
const char* pulseServiceURL = "http://10.0.0.88:8080/Pulse";
const int numReadings = 10;
float readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
float total = 0;                  // the running total
float average = 0;                // the average
static char weightstr[15];
Dispenser dp;

void setup()
{
  Wire.begin();               
  Serial.begin(115200);
  // Initialise dispenser

  // Connect to WiFi
  //WiFi.begin(wifiSsid, wifiPassword);

  //while (WiFi.status() != WL_CONNECTED) {
    //delay(500);
   // Serial.println("Connecting to WiFi...");
//  }

//  Serial.println("Connected to WiFi...");
//  Serial.println(WiFi.localIP());
dp.begin();

for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
 
}

void loop()
{
//  if (WiFi.status() == WL_CONNECTED) {
//    HTTPClient pulseClient;
//    pulseClient.setConnectTimeout(httpConnectionTimeout);
//    pulseClient.begin(pulseServiceURL);
//    int pulseResponseCode = pulseClient.GET();
//    pulseClient.end();

   // if (pulseResponseCode == 200) {
      // Continuosly check for rfid cards
        dp.getCardID();
      
        // Keep filling container until timout is reached
        unsigned long startTime = millis();
        //while (millis() - startTime < dispensingTimout) {
          float weight = dp.getWeight();
          // subtract the last reading:
           total = total - readings[readIndex];
          // read from the sensor:
          readings[readIndex] = weight;
          // add the reading to the total:
          total = total + readings[readIndex];
          // advance to the next position in the array:
          readIndex = readIndex + 1;

          // if we're at the end of the array...
          if (readIndex >= numReadings) {
          // ...wrap around to the beginning:
           readIndex = 0;
          }
          // calculate the average:
          average = total / numReadings;
         // send it to the computer as ASCII digits
//          Serial.println(average);
          delay(1);        // delay in between reads for stability
          dtostrf(average, 7, 5,weightstr);
          Serial.println(weightstr);
           Wire.beginTransmission(8); // transmit to device #8
           Wire.beginTransmission(9); // transmit to device #9
           Wire.write(weightstr);
           Wire.endTransmission();    // stop transmittig

       // }

        // Network sent data
//        String cardID = dp.getCardID();
//        String machineID = WiFi.macAddress();
//        float weightGrams = dp.getWeight();

        // Debug echo
//        Serial.println("Exiting dispensing mode.");
//        Serial.print("CardID: ");
//        Serial.println(dp.getCardID());
//        Serial.print("machineID: ");
//        Serial.println(machineID);
//        Serial.print("weightGrams: ");
//        Serial.println(weightGrams);

        // Send data over network
      //  if (weightGrams > 0) {
//          Serial.println("Sending Data to web service.");
//          String weightString = String(weightGrams);
//          itoa(weightGrams, weightString, 10);

//          String xml1 = "<CartItem xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns=\"http://schemas.datacontract.org/2004/07/Dispenser.WebService.Model\">\r\n";
//          String xml2a = "    <CardId>";
//          String xml2b = "</CardId>\r\n";
//          String xml3a = "    <MachineId>";
//          String xml3b = "</MachineId>\r\n";
//          String xml4a = "    <Weight>";
//          String xml4b = "</Weight>\r\n";
//          String xml5 = "</CartItem>";

//          String payload = xml1 + xml2a + dp.getCardID() + xml2b + xml3a + machineID + xml3b + xml4a + weightString + xml4b + xml5;
//          String payload = xml1 + xml2a + cardID + xml2b + xml3a + machineID + xml3b + xml4a + weightString + xml4b + xml5;
//          Serial.println(payload);

//          HTTPClient webclient;
//          webclient.setConnectTimeout(httpConnectionTimeout);
//          webclient.begin(cartServiceURL);
//          webclient.addHeader("Content-Type", "application/xml");
//          webclient.addHeader("Accept", "application/xml");
//          int httpResponseCode = webclient.POST(payload);

//          if (httpResponseCode == 200) {
//            Serial.println("Sending data: success");
//          } else {
//            Serial.println("Sending data: failed");
//          }
//          webclient.end();
       //}
//
//        dp.resetWeight();
        
    //  }
   // } 
    //else {
      //Serial.println("ERROR - Web service not available");
      // TO DO
      // Show on dispenser screen as that the dispense is offline
   // }
    //delay(500);
//    }//else {
    //Serial.println("ERROR - WiFi not connected...");
    // TO DO
    // Show on dispenser screen as no WiFi available
   // delay(500);
  //}
}
//void getcardID(){
//  Wire.requestFrom(8,11);    // request 11 bytes from slave device #8
//  while (Wire.available()) { // slave may send less than requested
//    char c = Wire.read(); // receive a byte as character
//   
//      Serial.print(c);         // print the character
//  }
//
//  Serial.println();
//}
