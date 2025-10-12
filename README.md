# LED control – Mechatronics IV



## 🖥️ Technologies Used

- **PLC programming** (e.g., Siemens TIA Portal or equivalent)
- **HMI/SCADA visualization**
- **Mechatronic system design**
- **CAD tools** for layout and schematics

---

## 📎 License

This project is for **educational purposes** as part of the *Mechatronics III* course.  
All rights reserved to the project authors and their institution.

---

##  API

"""
Simple REST API to control two LEDs (Flask)

Features:
- Endpoints:
  GET  /api/leds               -> returns states of both LEDs
  GET  /api/leds/<id>          -> returns state of LED id (1 or 2)
  PUT  /api/leds/<id>          -> set state with JSON {"state": "on"|"off"}
  POST /api/leds/<id>/toggle   -> toggle LED

- Uses RPi.GPIO if available; falls back to a simulated controller for development on non-RPi systems.

Example curl:
  # set LED 1 on
  curl -X PUT -H "Content-Type: application/json" -d '{"state":"on"}' http://localhost:5000/api/leds/1

  # get all
  curl http://localhost:5000/api/leds


---

## 📫 Contact

If you have any questions, feel free to reach out via the [Issues](https://github.com/your-repo/issues) tab.

---
