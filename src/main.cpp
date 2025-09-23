#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "ESP32AsyncOTA.h"

// Create server and OTA handler
AsyncWebServer server(80);
ESP32AsyncOTA ota(server);

// Your AP credentials
const char *ssid = "ESP32-OTA";
const char *password = "12345678";

void setup() {
  Serial.begin(115200);

  // Start WiFi in Access Point mode
  WiFi.softAP(ssid, password);
  Serial.println("AP started at: " + WiFi.softAPIP().toString());

  // Mount LittleFS
  if (!LittleFS.begin()) {
    Serial.println("LittleFS mount failed!");
    return;
  }

  // Serve index.html
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", "text/html");
  });

  // Enable OTA updates at /update
  ota.begin();

  // Start the server
  server.begin();
}

void loop() {

}
