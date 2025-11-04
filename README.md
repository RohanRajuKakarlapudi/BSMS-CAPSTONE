# BSMS-CAPSTONE
Full stack implementation of the Blind Spot Management System (BSMS); an IoT-based parking safety project using Arduino, ultrasonic sensors, and a React dashboard connected through the Web Serial API. The system provides real time blind spot detection, parking space monitoring, and visual alerts for both drivers and lot controllers.

# Blind Spot Management System (BSMS)

### Author: Sai Rohan Kakarlapudi  
University of Illinois Chicago | College of Engineering  
**Capstone Supervisor:** Evan McCarty  
**Capstone Fellow:** Prof. Luis Pina  
**Acknowledgment:** Patrick Troy  

Overview

Blind Spot Management System or **BSMS** is an IoT-based parking safety project built to help drivers and lot controllers detect blind spot risks in real time.  
Drivers often cannot see around sharp turns or blind corners in parking lots; this leads to slow movement, confusion, or small collisions.  
BSMS uses ultrasonic sensors, Arduino microcontrollers, and a web-based React dashboard to give instant visual and audio alerts when vehicles or pedestrians enter unsafe areas.

The system brings intelligence into the parking structure itself; it works for any car, regardless of make or age, and turns ordinary parking lots into connected, safer environments.

Users

- **Drivers:** Receive real-time LED and buzzer alerts when approaching hidden obstacles.  
- **Parking Lot Controllers:** Monitor live updates of blind spot activity, parking occupancy, and safety status through the dashboard.

System Architecture

1. **Sensor Layer:**  
   Each ultrasonic sensor measures distance using the HC-SR04 module.  
   The Arduino calculates proximity and sends live readings to the master controller.

2. **Processing Layer:**  
   A central Arduino board aggregates all sensor data and determines:  
   - Individual spot status (`TOO CLOSE`, `PERFECT POSITION`, `EMPTY SPOT`)  
   - Remaining parking spots  
   - Blind spot risk alerts (`POTENTIAL ACCIDENT`)

3. **Communication Layer:**  
   Data is transmitted to a connected computer over serial (9600 baud).  
   The browser reads this stream through the **Web Serial API**.

4. **Visualization Layer:**  
   The React dashboard displays live spot statuses and blind-spot alerts.  
   A dynamic L-shaped map updates visually as data changes.

Technology Stack

| Component | Technology |
|------------|-------------|
| **Microcontroller** | Arduino Uno / ESP32 |
| **Sensors** | HC-SR04 Ultrasonic Modules |
| **Frontend** | React.js, HTML, CSS |
| **Data Interface** | Web Serial API |
| **Programming Languages** | C++ (Arduino), JavaScript (React) |

Features

- Real-time blind spot detection and alerting  
- Visual map of parking layout (L-shape)  
- Spot availability tracking  
- LED and buzzer alert modules  
- Instant dashboard updates without page refresh  
- Works on any browser that supports Web Serial API (Chrome, Edge)

Hardware Setup

- HC-SR04 Ultrasonic Sensor (x10)  
- Arduino Uno or ESP32 microcontroller  
- LEDs (Red and Green)  
- Active Buzzer  
- 3D printed sensor cases for field deployment  
- Breadboard, jumper wires, and 10kΩ potentiometer  

All sensors are positioned to monitor parking spaces and one blind-corner intersection (BS001).  

© 2025 Sai Rohan Kakarlapudi. All rights reserved.
This project and its contents are protected under copyright law.
No part of this repository may be reproduced, distributed, or used for commercial purposes without explicit written permission from the author.

