/**
   A simple sketch to test and demo the dispenser's current features
*/

#include "DispenserData.h"
#include "DispenserUI.h"
#include "Dispenser.h"
#include <WiFi.h>
#include <HTTPClient.h>

// Const
const int dispensingTimout = 5000; //in milliseconds

// Wifi constants
const char* wifiSsid = "Crunchy";
const char* wifiPassword = "muffin4me";
const int httpConnectionTimeout = 500;
const char* cartServiceURL = "http://10.0.0.88:8080/Cart";
const char* pulseServiceURL = "http://10.0.0.88:8080/Pulse";

Dispenser dp;

void setup()
{
  Serial.begin(115200);
  // Initialise dispenser

  // Connect to WiFi
  WiFi.begin(wifiSsid, wifiPassword);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi...");
  Serial.println(WiFi.localIP());

  dp.begin();
  // Show product screen at startup
  dp.clearScreen();
  dp.showProductScreen();
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient pulseClient;
    pulseClient.setConnectTimeout(httpConnectionTimeout);
    pulseClient.begin(pulseServiceURL);
    int pulseResponseCode = pulseClient.GET();
    pulseClient.end();

    if (pulseResponseCode == 200) {
      // Continuosly check for rfid cards
      if (dp.isCardPresent()) {
        Serial.print("CardID: ");
        Serial.println(dp.getCardID());
        // If one is detected, toggle LED
        // and display sale screen
        dp.ledOn();
        dp.clearScreen();
        int prevWeight = 0;
        dp.showSaleScreen(0);

        // Keep filling container until timout is reached
        unsigned long startTime = millis();
        while (millis() - startTime < dispensingTimout) {
          int weight = dp.getWeight();
          if (weight > prevWeight) {
            dp.showSaleScreen(weight);
            prevWeight = weight;
          }
          // Toggle motor depending on whether
          // button is pressed
          if (dp.isButtonPressed()) {
            startTime = millis();
            Serial.println("Dispensing.");
            dp.addWeight();  // For Testing only
            dp.motorOn(255);
          } else {
            dp.motorOff();
          }
          delay(500);
        }

        // Network sent data
        String cardID = dp.getCardID();
        String machineID = WiFi.macAddress();
        unsigned int weightGrams = dp.getWeight();

        // Debug echo
        Serial.println("Exiting dispensing mode.");
        Serial.print("CardID: ");
        Serial.println(cardID);
        Serial.print("machineID: ");
        Serial.println(machineID);
        Serial.print("weightGrams: ");
        Serial.println(weightGrams);

        // Send data over network
        if (weightGrams > 0) {
          Serial.println("Sending Data to web service.");
          String weightString = String(weightGrams);
          //itoa(weightGrams, weightString, 10);

          String xml1 = "<CartItem xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns=\"http://schemas.datacontract.org/2004/07/Dispenser.WebService.Model\">\r\n";
          String xml2a = "    <CardId>";
          String xml2b = "</CardId>\r\n";
          String xml3a = "    <MachineId>";
          String xml3b = "</MachineId>\r\n";
          String xml4a = "    <Weight>";
          String xml4b = "</Weight>\r\n";
          String xml5 = "</CartItem>";

          String payload = xml1 + xml2a + cardID + xml2b + xml3a + machineID + xml3b + xml4a + weightString + xml4b + xml5;

          Serial.println(payload);

          HTTPClient webclient;
          webclient.setConnectTimeout(httpConnectionTimeout);
          webclient.begin(cartServiceURL);
          webclient.addHeader("Content-Type", "application/xml");
          webclient.addHeader("Accept", "application/xml");
          int httpResponseCode = webclient.POST(payload);

          if (httpResponseCode == 200) {
            Serial.println("Sending data: success");
          } else {
            Serial.println("Sending data: failed");
          }
          webclient.end();
        }

        // After timout, "stop dispensing",
        // and return to product screen
        dp.motorOff();
        dp.showSaleScreen(weightGrams);
        dp.ledOff();
        dp.resetWeight();

        // reset
        delay(2500);
        dp.clearScreen();
        dp.showProductScreen();
      }
    } else {
      Serial.println("ERROR - Web service not available");
      // TO DO
      // Show on dispenser screen as that the dispense is offline
    }
    delay(500);
  } else {
    Serial.println("ERROR - WiFi not connected...");
    // TO DO
    // Show on dispenser screen as no WiFi available
    delay(500);
  }
}
