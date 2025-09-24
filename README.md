# ESP32AsyncOTA
"Asynchronous OTA update handler for ESP32 (firmware + optional LittleFS). Used as a light weight option for Over-The-Air updates. Is able to be easily attached to any ESP32 project.
Utilizes the ESP32Async/ESPAsyncWebServer library to solve an issue that cam up with PlatformIO espota.py (Firewall keeps blocking ports required to normally OTA update). 

The update is served asynchronously at the designated localIP/update normally "192.168.4.1/update"

1. Build firmware or filesystem within PlatformIO or Arduino IDE.
2. Open web browser and navigate to "192.164.4.1/update".
3. Click Choose File button and navigate to binary file firmware.bin or littlefs.bin ("\.pio\build\firmware.bin" or "\.pio\build\littlefs.bin" for PlatformIO).
4. Click update button and wait.

The ESP32 will reset, and if successful changes will be reflected."


## Example code for library usage

```cpp
#include <Arduino.h>
#include <WiFi.h>
#include <LittleFS.h>
#include "ESP32AsyncOTA.h"

// Create server and OTA handler
AsyncWebServer server(80);
ESP32AsyncOTA ota(server);

// Your AP credentials
const char *ssid = "ESP32-OTA";
const char *password = "password123";

void setup() {
  Serial.begin(115200);

  // Start WiFi Access Point
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

  // Start the server to accept connections
  server.begin();
}

void loop() {
}
```

## Save in file data\index.html

```html
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 OTA Example</title>
</head>
<body>
  <h1>ESP32AsyncOTA</h1>
  <p>This page is served from LittleFS.</p>
  <p>To update firmware or filesystem, go to <a href="/update">/update</a>.</p>
</body>
</html>
```