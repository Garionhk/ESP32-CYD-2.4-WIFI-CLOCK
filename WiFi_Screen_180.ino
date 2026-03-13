#include "ArduinoJson.h"
#include <TimeLib.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
#include <HTTPClient.h>
// WiFiClient wifiClient;
#include <EEPROM.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define LCD_BL_PIN 5

// WiFi Credentials - USER: Replace with your details
const char *ssid = "YourWIFI";
const char *password = "YourPassword";

// NTP Server and Timezone
const char *ntpServer = "pool.ntp.org";
const char *timezone = "PST8PDT,M3.2.0,M11.1.0"; // Vancouver, BC

TFT_eSPI tft = TFT_eSPI();

void setup() {
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH); // This turns the backlight on
  Serial.begin(115200);

  // Initialize Display
  tft.init();
  tft.setRotation(3); // Landscape (rotated 180 deg clockwise from rotation 1)
  tft.invertDisplay(true); // Invert all colors
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Connecting to WiFi...", tft.width() / 2, tft.height() / 2, 4);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" WiFi Connected");
  tft.fillScreen(TFT_BLACK);
  tft.drawString("WiFi Connected", tft.width() / 2, tft.height() / 2, 4);
  delay(1000);

  // Init and get the time with automatic DST handling
  configTzTime(timezone, ntpServer);
  tft.fillScreen(TFT_BLACK);
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    tft.drawString("Failed to obtain time", tft.width() / 2, tft.height() / 2,
                   2);
    return;
  }

  char timeString[6]; // "HH:MM"
  char dateString[20];

  // Format: HH:MM or HH MM based on seconds parity for flashing effect
  if (timeinfo.tm_sec % 2 == 0) {
    strftime(timeString, sizeof(timeString), "%H:%M", &timeinfo);
  } else {
    strftime(timeString, sizeof(timeString), "%H %M", &timeinfo);
  }

  // Format: Month Day, Year
  strftime(dateString, sizeof(dateString), "%B %d, %Y", &timeinfo);

  // Render Banner at the top
  tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
  tft.drawString("Garion Photo Tech", tft.width() / 2, 20,
                 2); // Font 2 is pixel-style

  // Render Large Clock
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString(timeString, tft.width() / 2, tft.height() / 2,
                 7); // Using Font 7 (Digital style)
  tft.setTextSize(1);

  // Render Date below in green pixel style
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString(dateString, tft.width() / 2, (tft.height() / 2) + 80,
                 4); // Font 4 is also pixel-ish/clean
}

void loop() {
  printLocalTime();
  delay(1000); // Update every second
}
