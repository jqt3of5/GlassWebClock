#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266mDNS.h>
#include <WiFiClientSecure.h>
#include "certs.h"
#include "api.h"
#include "dotstar5050.h"

WiFiClientSecure client;
ESP8266WebServerSecure server(443);

X509List cacert(ca);
X509List cert(x509);
PrivateKey key(rsakey);

const int led = 2;

//TODO: Really should be persisted in flash memory
int timeZone = 6;


void startSoftAP()
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

bool connectToLastAP()
{
  Serial.print("Connecting To AP");
  WiFi.begin();

  int retryCount = 20;
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led, HIGH);
    delay(250);
    digitalWrite(led, LOW);
    delay(250);
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
    digitalWrite(led, HIGH);
    return false;
  }
  
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(led, LOW);
  return true;
}

void connectToNTP()
{
  Serial.print("getting time from ntp");
  configTime(timeZone * 3600, 0, "pool.ntp.org", "ime.nist.gov");
}
bool connectToMQTT()
{
  
}

void startConfigServer()
{
  server.getServer().setServerKeyAndCert_P((const uint8_t*)rsakey, sizeof(rsakey), (const uint8_t*)x509, sizeof(x509));
  server.on("/", handleRoot);
  server.on("/scan", handleScanWiFi);
  server.on("/wifiCreds", handleWiFiCreds);
  server.on("/timezone",handleSetTimeZone);
  server.on("/time", handleSetTime);
  server.on("/custom", handleCustomLED);
  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTPS server started");
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  Serial.begin(115200);

  client.setTrustAnchors(&cacert);
  client.setClientRSACert(&cert, &key);

  //Check if we start in connected mode, eg. connect to the last wifi AP
  if (connectToLastAP())
    {
      connectToNTP();
      connectToMQTT();
    }
  else
    {
      //setup in Config mode with the soft AP
      startSoftAP();
    }
 
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  startConfigServer();

}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
