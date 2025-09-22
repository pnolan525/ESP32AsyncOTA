#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "ESP32AsyncOTA.h"

AsyncWebServer server(80);
ESP32AsyncOTA ota(server);

const char *ssid = "ESP32-OTA";
const char *password = "12345678";

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  Serial.println("AP started at: " + WiFi.softAPIP().toString());

  ota.begin();  // now /update works
  server.begin();
}

void loop() {
}
