
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266mDNS.h>

#include "certs.h"
#include "api.h"
#include "dotstar5050.h"

const char* ssid = "WaitingOnComcast";
const char* password = "1594N2640W";

ESP8266WebServerSecure server(443);

const int led = 2;

void setupConfigMode()
{
  if (WiFi.softAP("esp8266", "testtest123"))
  {
    Serial.println("softAP started");
  }
  delay(100);
  Serial.println("");

  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.println(WiFi.localIP());
}

bool setupConnectedMode(const char * ssid,const char * pwd)
{
  Serial.print("Connecting To AP: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int retryCount = 20;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
    Serial.print(WiFi.status());
    Serial.print(".");
    
    if (retryCount == 0)
    {
      break;
    }
    retryCount -= 1;
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Failed to connect, WiFi Status: ");
    Serial.println(WiFi.status());
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

  server.getServer().setServerKeyAndCert_P(rsakey, sizeof(rsakey), x509, sizeof(x509));

  server.on("/", handleRoot);
  server.on("/wifi", handleWiFiCreds);
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
