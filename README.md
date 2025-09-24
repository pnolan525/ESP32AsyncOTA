# ESP32AsyncOTA
"Asynchronous OTA update handler for ESP32 (firmware + optional LittleFS). Used as a light weight option for Over-The-Air updates. Is able to be easily attached to any ESP32 project.
Utilizes the ESP32Async/ESPAsyncWebServer library to solve an issue that cam up with PlatformIO espota.py (Firewall keeps blocking ports required to normally OTA update). 

The update is served asynchronously at the designated localIP/update normally "192.168.4.1/update"

1. Build firmware or filesystem within PlatformIO or Arduino IDE.
2. Open web browser and navigate to "192.164.4.1/update".
3. Click Choose File button and navigate to binary file firmware.bin or littlefs.bin ("\.pio\build\firmware.bin" or "\.pio\build\littlefs.bin" for PlatformIO).
4. Click update button and wait.

The ESP32 will reset and if successful changes will be reflected."
