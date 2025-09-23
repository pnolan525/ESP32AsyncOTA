#include "ESP32AsyncOTA.h"

ESP32AsyncOTA::ESP32AsyncOTA(AsyncWebServer &server) : _server(server) {}

void ESP32AsyncOTA::begin(const char *username, const char *password) {
  _username = username;
  _password = password;

  // Serve the OTA upload page
  _server.on("/update", HTTP_GET, [&](AsyncWebServerRequest *request) {
    if (_username.length() && _password.length() && !request->authenticate(_username.c_str(), _password.c_str())) {
      return request->requestAuthentication();
    }
    handleUpdatePage(request);
  });

  // Handle the OTA upload
  _server.on("/update", HTTP_POST,
    [&](AsyncWebServerRequest *request) {
      bool ok = !Update.hasError();
      request->send(ok ? 200 : 500, "text/plain", ok ? "Update Success, rebooting..." : "Update Failed");
      if (ok) {
        delay(500);
        ESP.restart();
      }
    },
    [&](AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final) {
      handleUpload(request, filename, index, data, len, final);
    }
  );
}

void ESP32AsyncOTA::handleUpdatePage(AsyncWebServerRequest *request) {
  String page =
    "<!DOCTYPE html><html><head><meta charset='utf-8'>"
    "<title>ESP32 OTA Update</title></head><body>"
    "<h2>ESP32 Async OTA Update</h2>"
    "<form method='POST' action='/update' enctype='multipart/form-data'>"
    "<input type='file' name='update'>"
    "<input type='submit' value='Update'>"
    "</form>"
    "</body></html>";
  request->send(200, "text/html", page);
}

void ESP32AsyncOTA::handleUpload(AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final) {
if (!index) {
  	bool isFs = filename.endsWith(".bin") && filename.indexOf("littlefs") >= 0;
#if HAS_LITTLEFS
    if (isFs) {
      if (!Update.begin(LittleFS.totalBytes(), U_SPIFFS)) {
        Update.printError(Serial);
      }
    } else
#endif
    {
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
        Update.printError(Serial);
      }
    }
  }

  if (len) {
    if (Update.write(data, len) != len) {
      Update.printError(Serial);
    }
  }

  if (final) {
    if (!Update.end(true)) {
      Update.printError(Serial);
    }
  }
}
