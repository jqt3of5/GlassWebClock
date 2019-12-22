
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266mDNS.h>

#include "certs.h"
#include "api.h"

const char* ssid = "";
const char* password = "";

ESP8266WebServerSecure server(443);

const int led = 13;

void setupConfigMode()
{
  if (WiFi.softAp("esp8266"))
  {
    Serial.println("softAP started");
  }
  
  Serial.println("");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

bool setupConnectedMode(char * ssid, char * pwd)
{
  Serial.println("Connecting To AP: %d", ssid);
   WiFi.begin(ssid, password);
   
   while (WiFi.status() == WL_IDLE_STATUS) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Failed to connect, WiFi Status: %d", WiFi.Status());
    return false;
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);

  //Check if we start in connected mode, eg. connect to the last wifi AP
  if (!setupConnectedMode(ssid, password))
  {
    //setup in Config mode with the soft AP
    setupConfigMode();
  }
  
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.setServerKeyAndCert_P(rsakey, sizeof(rsakey), x509, sizeof(x509));

  server.on("/", handleRoot);
  server.on("/wifi", handleWifiCreds);
  server.on("/timezone",handleSetTimeZone);
  server.on("/time", handleSetTime);
  server.on("/custom", handleCustomLED);
  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTPS server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
