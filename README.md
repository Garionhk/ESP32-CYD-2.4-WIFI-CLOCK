# ESP32 WiFi Clock (CYD)

A beautiful and functional WiFi-connected clock designed for the **"Cheap Yellow Display" (CYD)** - ESP32-2432S024 . This project displays the current time and date with a sleek digital interface.

## 🚀 Features
- **WiFi Synchronized**: Automatically sets and maintains time via NTP.
- **Automatic DST**: Handles Daylight Saving Time changes automatically.
- **Digital Aesthetics**: Features a large LED-style clock and date display.
- **Custom Banner**: Displays "Garion Photo Tech" banner at the top.

## 🛠 Hardware Required
- **ESP32-2432S024**: Also known as the "Cheap Yellow Display" (2.8" or 2.4" TFT with Touch).

## 📚 Libraries
This project requires several libraries for the display, JSON parsing, and time management. It is highly recommended to use the **attached libraries** provided in the `libraries/` folder to ensure compatibility.

**Included Libraries:**
- `TFT_eSPI`: Main display driver.
- `TJpg_Decoder`: For JPEG image decoding.
- `ArduinoJson`: JSON parsing for configuration or API data.
- `TimeLib`: Time management.

### Installation via Attached Libraries
1. Locate the `libraries/` folder in this project.
2. Copy all sub-folders within `libraries/` to your Arduino `libraries` directory (usually located at `Documents/Arduino/libraries/`).

## ⚙️ Configuration
Before uploading to your device, update the following variables in `WiFi_Screen_180.ino`:

### WiFi Settings
Update lines 17-18 with your WiFi credentials:
```cpp
const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";
```

### Timezone
The default timezone is set to Vancouver, BC (PST/PDT):
```cpp
const char *timezone = "PST8PDT,M3.2.0,M11.1.0";
```
You can modify this string to match your local timezone.

## 🔄 Screen Rotation (180°)
The program is currently configured to rotate the screen **180 degrees** (Landscape flipped).

To revert this or use the standard orientation, locate the following line in the `setup()` function:
```cpp
tft.setRotation(3); // Landscape (rotated 180 deg clockwise from rotation 1)
```

**To use the standard orientation (Rotation 1), change it to:**
```cpp
tft.setRotation(1); 
```
Or simply comment out the line if you prefer the default hardware orientation.

---

*Developed for the Cheap Yellow Display community.*
