#pragma once
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Update.h>

#if __has_include(<LittleFS.h>)
  #include <LittleFS.h>
  #define HAS_LITTLEFS 1
#else
  #define HAS_LITTLEFS 0
#endif

class ESP32AsyncOTA {
public:
  ESP32AsyncOTA(AsyncWebServer &server);
  void begin(const char *username = "", const char *password = "");

private:
  AsyncWebServer &_server;
  String _username;
  String _password;

  void handleUpdatePage(AsyncWebServerRequest *request);
  void handleUpload(AsyncWebServerRequest *request,
                    const String &filename, size_t index,
                    uint8_t *data, size_t len, bool final);
};
