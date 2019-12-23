/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 2; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("WaitingOnComcast", "1594N2640W");

  Serial.printf("WIFI Connected\n");
  pinMode(4, OUTPUT); // Hours
  pinMode(5, OUTPUT); // Minutes
  pinMode(0, OUTPUT); // Clock
  digitalWrite(0, 1);
  
  int hours[6] = {0xFFFFFF,0xFFFFFF,0xFF0000,0x00FF00,0x0000FF,0x000000};
  int minutes[6] = {0xFFFFFF,0xFFFFFF,0xFF0000,0x00FF00,0x0000FF,0x0000FF};
  
  //start frame
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  for (int mask = 0; mask < 32; ++mask)
  {
    digitalWrite(0, 0);  
    delay(10);
    digitalWrite(0, 1);
    delay(10);
  }

  for (int i = 4; i >= 0; --i)
  {
    digitalWrite(4, 1);
    digitalWrite(5, 1);
    for (int mask = 0; mask < 3; ++mask)
    {
      digitalWrite(0, 0);      
      delay(10);
      digitalWrite(0, 1);
      delay(10);
    }
    //Global
    int global = 1 << 4;
    for (int mask = 0; mask < 5; ++mask)
    {
      digitalWrite(4, (global & 1 << mask) ? 1 : 0);
      digitalWrite(5, (global & 1 << mask) ? 1 : 0);
      
      digitalWrite(0, 0);
      delay(10);
      digitalWrite(0, 1);
      delay(10);
    }
    //Color
    for (int mask = 0; mask < 24; ++mask)
    {
      digitalWrite(4, (hours[i] & 1 << mask) ? 1 : 0);
      digitalWrite(5, (minutes[i] & 1 << mask) ? 1 : 0);
      
      digitalWrite(0, 0);
      delay(10);
      digitalWrite(0, 1);
      delay(10);
    }
  }
  
  //end frame
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  for (int mask = 0; mask < 32; ++mask)
  {
    digitalWrite(0, 0);
    delay(10);
    digitalWrite(0, 1);
    delay(10);
  }
  Serial.printf("Data Written\n");
}

void loop() {

  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;
    
    //Serial.print("[HTTP] begin...\n");
    /*if (http.begin(client, "http://jigsaw.w3.org/HTTP/connection.html")) {  // HTTP
      
      digitalWrite(2, HIGH);
      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }*/
  }


}
