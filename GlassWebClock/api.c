
extern ESP8266WebServerSecure server;
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

// POST "/wifi"
void handleWiFiCreds() {
  if (server.method() != HTTP_POST)
  {
    handleNotFound();
    return;
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