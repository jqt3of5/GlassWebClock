#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <ESP8266WebServerSecure.h>

extern ESP8266WebServerSecure server;
const int led = 13;
// GET "/"
void handleRoot() {
  digitalWrite(led, 1);
  
  server.send(200, "text/plain", "Hello from esp8266 over HTTPS!");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

//GET "/scan"
void handleScanWiFi()
{
  char * buffer;
  int bufferSize = 0;
  
  int n = WiFi.scanNetworks();
  for(int i = 0; i < n; ++i)
  {
    String wifi = WiFi.SSID(i);
    bufferSize += wifi.length() + 1;
    Serial.println(WiFi.SSID(i));   
  }  

  buffer = (char*)calloc(sizeof(char), bufferSize +1);
  for (int i = 0; i < n; ++i)
  {
    String wifi = WiFi.SSID(i);
    strncat(buffer, wifi.c_str(), wifi.length());
    strncat(buffer, ",", 1);
  }

  server.send(200, "text/plain", buffer);
}

// POST "/wifiCreds"
void handleWiFiCreds() {
  /*if (server.method() != HTTP_POST)
  {
    handleNotFound();
    return;
  }*/
  const char * ssid = 0, *password = 0;
  for (int i = 0; i < server.args(); ++i)
  {
    Serial.println(server.argName(i));
    Serial.println(server.arg(i));
    if (server.argName(i) == "ssid")
    {
      ssid = server.arg(i).c_str();
    }
    else 
    if (server.argName(i) == "password")
    {
      password = server.arg(i).c_str();
    }
  }

  if (ssid != 0)
  {
    WiFi.begin(ssid, password);
  }  
}

// POST "/timezone"
void handleSetTimeZone() {
  
}

// POST "/time"
void handleSetTime() {
  
}

//POST "/custom"
void handleCustomLED() {
  
}
