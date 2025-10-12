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


---
