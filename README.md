# LED control – Mechatronics IV

---

## 📎 License

This project is for **educational purposes** as part of the *Mechatronics MUP IV semester* course.  
All rights reserved to the project authors and their institution.

## Features
💡 LED Control

Toggle individual LEDs (1–4) remotely via a web interface.

Query LED states using JSON API:

GET /api/leds/{id} → { "id": n, "state": "on"|"off" }
POST /api/leds/{id}/toggle → toggles the LED and returns new state


Real-time feedback in the web dashboard using AJAX.

<img width="685" height="784" alt="image" src="https://github.com/user-attachments/assets/7a637205-cd0f-4663-8531-3721a2da9233" />

## 📦 OTA Firmware Updates

Upload new firmware directly from the web interface.

Progress bar with percentage updates.

Automatic flashing and reboot to the new firmware.

JSON API for OTA status:

POST /OTAstatus → { "ota_update_status": 0|1|-1, "compile_time": "...", "compile_date": "..." }

<img width="692" height="460" alt="image" src="https://github.com/user-attachments/assets/253399aa-7e20-4ee7-9613-1f1936c4348d" />

<img width="696" height="554" alt="image" src="https://github.com/user-attachments/assets/cb90c256-c799-43de-9c3a-50cc67cd06fb" />


## 📶 Wi-Fi & Network Configuration

View and modify network SSID and password via the web interface.

Save settings to non-volatile storage (NVS).

Retrieve current device IP address:

GET /api/config/ip_addr → { "ip": "192.168.0.X" }
GET /api/config/network → { "ssid": "...", "password": "..." }
POST /api/config/network → save new credentials

<img width="637" height="550" alt="image" src="https://github.com/user-attachments/assets/e2e20f08-bfec-4e5a-8705-ccacb3ec3c87" />

## 🖥️ Web Interface

Fully responsive dashboard served by the ESP’s internal web server.

Built with:

index.html

app.js for dynamic behavior

app.css for styling

jQuery 3.3.1

## ⚡ Efficient HTTP Server

Custom HTTP server using ESP-IDF’s httpd module.

Handles static files (HTML, CSS, JS, favicon.ico).

Provides RESTful endpoints for LEDs, OTA, and network management.

Designed for robustness with CORS support, JSON handling, and OTA error recovery.

## 🔧 Project Highlights

Multi-tasking with FreeRTOS: HTTP server and monitoring task run concurrently.

Supports concurrent requests for LED control and OTA updates.

Modular code: easy to extend for additional sensors or actuators.
