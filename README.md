# LED control – Mechatronics IV


---

## 📎 License

This project is for **educational purposes** as part of the *Mechatronics III* course.  
All rights reserved to the project authors and their institution.

---

##  API

"""
🔌 API LED
1️⃣ Odczyt stanu LED (GET)
Endpointy:

GET /api/leds/1 — odczyt stanu diody LED 1

GET /api/leds/2 — odczyt stanu diody LED 2

Opis:

Zwraca aktualny stan danej diody w formacie JSON (on lub off).

Odpowiedź (200 OK):
{
  "id": 1,
  "state": "on"
}

Przykłady curl:
curl http://localhost:5000/api/leds/1
curl http://localhost:5000/api/leds/2

2️⃣ Przełączanie stanu LED (POST)
Endpointy:

POST /api/leds/1/toggle — zmiana stanu diody LED 1

POST /api/leds/2/toggle — zmiana stanu diody LED 2

Opis:

Zmienia stan diody na przeciwny — jeśli była on, zostanie off, i odwrotnie.
Nie wymaga żadnego ciała żądania (body).

Odpowiedź (200 OK):
{
  "id": 1,
  "state": "off"
}

Przykłady curl:
curl -X POST http://localhost:5000/api/leds/1/toggle
curl -X POST http://localhost:5000/api/leds/2/toggle

📡 REST API — Network Configuration

Base URL:

http://<device_ip_address>/api/config/network


This endpoint allows the frontend to get and set the Wi-Fi network configuration (SSID and password) stored on the ESP32.

1️⃣ GET /api/config/network

Description:
Retrieve the currently stored network credentials (SSID and password) from the ESP32.

Request:

GET /api/config/network


Headers:

Content-Type: application/json


Response:

{
  "ssid": "MyWiFi",
  "password": "MySecretPassword"
}


If no data is found:

{
  "serial_number": null
}


Status Codes:

200 OK – Data successfully retrieved

500 Internal Server Error – Failed to load data from NVS

2️⃣ POST /api/config/network

Description:
Save new Wi-Fi credentials (SSID and password) to the ESP32’s NVS storage.

Request:

POST /api/config/network


Headers:

Content-Type: application/json


Body (JSON):

{
  "ssid": "MyWiFi",
  "password": "MySecretPassword"
}


Response (Success):

Serial set


Status Codes:

200 OK – Data saved successfully

400 Bad Request – Invalid or missing JSON fields

500 Internal Server Error – Failed to save data


---
