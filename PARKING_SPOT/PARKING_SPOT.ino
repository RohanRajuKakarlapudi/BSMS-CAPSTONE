// // // // // // #include <LiquidCrystal.h>

// // // // // // // Initialize the LCD library with the numbers of the interface pins

// // // // // // const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// // // // // // LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// // // // // // #define trigPin     6
// // // // // // #define echoPin     7
// // // // // // #define redLED      8
// // // // // // #define yellowLED   9
// // // // // // #define greenLED    10
// // // // // // #define buzzer      13

// // // // // // unsigned long previousMillis       = 0;
// // // // // // unsigned long previousSensorMillis = 0;
// // // // // // const unsigned long interval       = 500; // blink interval (ms)
// // // // // // const unsigned long sensorInterval = 50;  // sensor read interval (ms)

// // // // // // String currentStatus = "";
// // // // // // String lastStatus    = "";

// // // // // // void setup() {
// // // // // //   // LCD
// // // // // //   lcd.begin(16, 2);
// // // // // //   lcd.clear();

// // // // // //   // LEDs & buzzer
// // // // // //   pinMode(redLED, OUTPUT);
// // // // // //   pinMode(yellowLED, OUTPUT);
// // // // // //   pinMode(greenLED, OUTPUT);
// // // // // //   pinMode(buzzer, OUTPUT);

// // // // // //   // Ultrasonic
// // // // // //   pinMode(trigPin, OUTPUT);
// // // // // //   pinMode(echoPin, INPUT);

// // // // // //   Serial.begin(9600);
// // // // // // }

// // // // // // void loop() {
// // // // // //   unsigned long currentMillis = millis();

// // // // // //   // Serial command echo (unchanged)
// // // // // //   if (Serial.available()) {
// // // // // //     String received = Serial.readStringUntil('\n');
// // // // // //     received.trim();
// // // // // //     Serial.print("Received command: ");
// // // // // //     Serial.println(received);
// // // // // //   }

// // // // // //   // Distance measurement on a regular interval
// // // // // //   if (currentMillis - previousSensorMillis >= sensorInterval) {
// // // // // //     previousSensorMillis = currentMillis;
// // // // // //     measureDistance();
// // // // // //   }

// // // // // //   // Flash yellow if object is moving
// // // // // //   if (currentStatus == "OBJECT MOVING" && (currentMillis - previousMillis >= interval)) {
// // // // // //     previousMillis = currentMillis;
// // // // // //     digitalWrite(yellowLED, !digitalRead(yellowLED));
// // // // // //   } else if (currentStatus != "OBJECT MOVING") {
// // // // // //     digitalWrite(yellowLED, LOW);
// // // // // //   }
// // // // // // }

// // // // // // void measureDistance() {
// // // // // //   // Trigger the ultrasonic burst
// // // // // //   digitalWrite(trigPin, LOW);
// // // // // //   delayMicroseconds(2);
// // // // // //   digitalWrite(trigPin, HIGH);
// // // // // //   delayMicroseconds(10);
// // // // // //   digitalWrite(trigPin, LOW);

// // // // // //   long duration = pulseIn(echoPin, HIGH);
// // // // // //   long distance = (duration / 2) / 30; // in cm

// // // // // //   updateStatus(distance);
// // // // // // }

// // // // // // void updateStatus(long distance) {
// // // // // //   // Decide status
// // // // // //   if (distance < 4) {
// // // // // //     currentStatus = "TOO CLOSE";
// // // // // //   }
// // // // // //   else if (distance < 8) {
// // // // // //     currentStatus = "PERFECT POSITION";
// // // // // //     Serial.println("Spot occupied");
// // // // // //   }
// // // // // //   else if (distance < 12) {
// // // // // //     currentStatus = "OBJECT MOVING";
// // // // // //     Serial.println("OBJ MOVING");
// // // // // //   }
// // // // // //   else {
// // // // // //     currentStatus = "EMPTY SPOT";
// // // // // //     Serial.println("Spot empty");
// // // // // //   }

// // // // // //   // Redraw only on change
// // // // // //   if (currentStatus != lastStatus) {
// // // // // //     lastStatus = currentStatus;
// // // // // //     lcd.clear();
// // // // // //     lcd.setCursor(0, 1);
// // // // // //     lcd.print(currentStatus);
// // // // // //   }

// // // // // //   // Always show distance
// // // // // //   lcd.setCursor(0, 0);
// // // // // //   lcd.print("Dist: ");
// // // // // //   lcd.print(distance);
// // // // // //   lcd.print(" cm   ");

// // // // // //   // LEDs & buzzer
// // // // // //   bool redOn   = (currentStatus == "TOO CLOSE");
// // // // // //   bool greenOn = (currentStatus == "EMPTY SPOT");
  
// // // // // //   digitalWrite(redLED,   redOn);
// // // // // //   digitalWrite(greenLED, greenOn);
// // // // // //   digitalWrite(buzzer,   redOn);  // buzzer follows red LED
// // // // // // }



// // // // // // ///// I can reserve a spot through serial monitor, if i do, then if someone tries to park their car , the yellow and red if someone tries to park there 

// // // // // // -------- Parking Spot Manager --------
// // // // // #include <LiquidCrystal.h>
// // // // // #include <SoftwareSerial.h>

// // // // // // LCD pins
// // // // // const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// // // // // LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// // // // // // ultrasonic + LEDs + buzzer
// // // // // #define trigPin     6
// // // // // #define echoPin     7
// // // // // #define redLED      8
// // // // // #define yellowLED   9
// // // // // #define greenLED    10
// // // // // #define buzzer      13

// // // // // // comm to BSMS: RX on 2, TX on 3
// // // // // SoftwareSerial comm(0, 1);

// // // // // unsigned long previousMillis       = 0;
// // // // // unsigned long previousSensorMillis = 0;
// // // // // const unsigned long interval       = 500; // blink interval (ms)
// // // // // const unsigned long sensorInterval = 50;  // sensor read interval (ms)

// // // // // String currentStatus = "";
// // // // // String lastStatus    = "";
// // // // // int    spotsLeft     = 10;
// // // // // bool   lastOccupied  = false;

// // // // // void setup() {
// // // // //   // LCD
// // // // //   lcd.begin(16, 2);
// // // // //   lcd.clear();

// // // // //   // LEDs & buzzer
// // // // //   pinMode(redLED, OUTPUT);
// // // // //   pinMode(yellowLED, OUTPUT);
// // // // //   pinMode(greenLED, OUTPUT);
// // // // //   pinMode(buzzer, OUTPUT);

// // // // //   // Ultrasonic
// // // // //   pinMode(trigPin, OUTPUT);
// // // // //   pinMode(echoPin, INPUT);

// // // // //   // comms
// // // // //   comm.begin(9600);
// // // // //   // Serial.begin(9600); // commented out per request
// // // // // }

// // // // // void loop() {
// // // // //   unsigned long currentMillis = millis();

// // // // //   // Distance measurement on a regular interval
// // // // //   if (currentMillis - previousSensorMillis >= sensorInterval) {
// // // // //     previousSensorMillis = currentMillis;
// // // // //     measureDistance();
// // // // //   }

// // // // //   // Flash yellow if object is moving
// // // // //   if (currentStatus == "OBJECT MOVING" && (currentMillis - previousMillis >= interval)) {
// // // // //     previousMillis = currentMillis;
// // // // //     digitalWrite(yellowLED, !digitalRead(yellowLED));
// // // // //   } else if (currentStatus != "OBJECT MOVING") {
// // // // //     digitalWrite(yellowLED, LOW);
// // // // //   }
// // // // // }

// // // // // void measureDistance() {
// // // // //   // Trigger the ultrasonic burst
// // // // //   digitalWrite(trigPin, LOW);
// // // // //   delayMicroseconds(2);
// // // // //   digitalWrite(trigPin, HIGH);
// // // // //   delayMicroseconds(10);
// // // // //   digitalWrite(trigPin, LOW);

// // // // //   long duration = pulseIn(echoPin, HIGH);
// // // // //   long distance = (duration / 2) / 30; // in cm

// // // // //   updateStatus(distance);
// // // // // }

// // // // // void updateStatus(long distance) {
// // // // //   // Determine occupancy
// // // // //   bool nowOccupied;
// // // // //   if (distance < 4) {
// // // // //     currentStatus = "TOO CLOSE";
// // // // //     nowOccupied   = true;
// // // // //   }
// // // // //   else if (distance < 8) {
// // // // //     currentStatus = "PERFECT POSITION";
// // // // //     nowOccupied   = true;
// // // // //     // Serial.println("Spot occupied"); // commented out
// // // // //   }
// // // // //   else if (distance < 12) {
// // // // //     currentStatus = "OBJECT MOVING";
// // // // //     nowOccupied   = false;
// // // // //     // Serial.println("OBJ MOVING"); // commented out
// // // // //   }
// // // // //   else {
// // // // //     currentStatus = "EMPTY SPOT";
// // // // //     nowOccupied   = false;
// // // // //     // Serial.println("Spot empty"); // commented out
// // // // //   }

// // // // //   // Redraw only on change
// // // // //   if (currentStatus != lastStatus) {
// // // // //     lastStatus = currentStatus;
// // // // //     lcd.clear();
// // // // //     lcd.setCursor(0, 1);
// // // // //     lcd.print(currentStatus);
// // // // //   }

// // // // //   // Always show distance
// // // // //   lcd.setCursor(0, 0);
// // // // //   lcd.print("Dist: ");
// // // // //   lcd.print(distance);
// // // // //   lcd.print(" cm   ");

// // // // //   // LEDs & buzzer
// // // // //   bool redOn   = (currentStatus == "TOO CLOSE");
// // // // //   bool greenOn = (currentStatus == "EMPTY SPOT");

// // // // //   digitalWrite(redLED,   redOn);
// // // // //   digitalWrite(greenLED, greenOn);
// // // // //   digitalWrite(buzzer,   redOn);  // buzzer follows red LED

// // // // //   // Send update only on occupancy change
// // // // //   if (nowOccupied != lastOccupied) {
// // // // //     lastOccupied = nowOccupied;
// // // // //     spotsLeft   += nowOccupied ? -1 : +1;
// // // // //     comm.print("PARK,");
// // // // //     comm.print(nowOccupied ? 1 : 0);
// // // // //     comm.print(",");
// // // // //     comm.println(spotsLeft);
// // // // //   }
// // // // // }


// // // // #include <LiquidCrystal.h>
// // // // #include <SoftwareSerial.h>

// // // // // LCD pins
// // // // const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// // // // LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// // // // // Ultrasonic + LEDs + buzzer
// // // // #define trigPin    6
// // // // #define echoPin    7
// // // // #define redLED     8
// // // // #define yellowLED  9
// // // // #define greenLED   10
// // // // #define buzzerPin  13

// // // // // SoftwareSerial: RX on 2, TX on 3
// // // // SoftwareSerial comm(2, 3);

// // // // unsigned long prevMillis        = 0;
// // // // unsigned long prevSensorMillis  = 0;
// // // // const unsigned long blinkInterval  = 500;  // yellow blink
// // // // const unsigned long sensorInterval = 50;   // distance read

// // // // String currentStatus = "";
// // // // String lastStatus    = "";
// // // // bool   lastOccupied  = false;
// // // // int    spotsLeft     = 10;

// // // // void setup() {
// // // //   // LCD
// // // //   lcd.begin(16, 2);
// // // //   lcd.clear();

// // // //   // LEDs & buzzer
// // // //   pinMode(redLED, OUTPUT);
// // // //   pinMode(yellowLED, OUTPUT);
// // // //   pinMode(greenLED, OUTPUT);
// // // //   pinMode(buzzerPin, OUTPUT);

// // // //   // Ultrasonic
// // // //   pinMode(trigPin, OUTPUT);
// // // //   pinMode(echoPin, INPUT);

// // // //   // Comm link
// // // //   comm.begin(9600);
// // // //   // Serial.begin(9600); // no longer needed for PARK messages
// // // // }

// // // // void loop() {
// // // //   unsigned long now = millis();

// // // //   // Read distance every sensorInterval
// // // //   if (now - prevSensorMillis >= sensorInterval) {
// // // //     prevSensorMillis = now;
// // // //     measureDistance();
// // // //   }

// // // //   // Flash yellow if “OBJECT MOVING”
// // // //   if (currentStatus == "OBJECT MOVING" && (now - prevMillis >= blinkInterval)) {
// // // //     prevMillis = now;
// // // //     digitalWrite(yellowLED, !digitalRead(yellowLED));
// // // //   } else if (currentStatus != "OBJECT MOVING") {
// // // //     digitalWrite(yellowLED, LOW);
// // // //   }
// // // // }

// // // // void measureDistance() {
// // // //   // Trigger burst
// // // //   digitalWrite(trigPin, LOW);
// // // //   delayMicroseconds(2);
// // // //   digitalWrite(trigPin, HIGH);
// // // //   delayMicroseconds(10);
// // // //   digitalWrite(trigPin, LOW);

// // // //   long duration = pulseIn(echoPin, HIGH);
// // // //   long distance = (duration / 2) / 30; // cm

// // // //   updateStatus(distance);
// // // // }

// // // // void updateStatus(long dist) {
// // // //   bool nowOccupied;

// // // //   if (dist < 4) {
// // // //     currentStatus = "TOO CLOSE";
// // // //     nowOccupied   = true;
// // // //   }
// // // //   else if (dist < 8) {
// // // //     currentStatus = "PERFECT POSITION";
// // // //     nowOccupied   = true;
// // // //     // Serial.println("Spot occupied");  // commented out
// // // //   }
// // // //   else if (dist < 12) {
// // // //     currentStatus = "OBJECT MOVING";
// // // //     nowOccupied   = false;
// // // //     // Serial.println("OBJ MOVING");     // commented out
// // // //   }
// // // //   else {
// // // //     currentStatus = "EMPTY SPOT";
// // // //     nowOccupied   = false;
// // // //     // Serial.println("Spot empty");     // commented out
// // // //   }

// // // //   // Redraw LCD on status change
// // // //   if (currentStatus != lastStatus) {
// // // //     lastStatus = currentStatus;
// // // //     lcd.clear();
// // // //     lcd.setCursor(0, 1);
// // // //     lcd.print(currentStatus);
// // // //   }

// // // //   // Always show distance
// // // //   lcd.setCursor(0, 0);
// // // //   lcd.print("Dist: ");
// // // //   lcd.print(dist);
// // // //   lcd.print(" cm   ");

// // // //   // LEDs & buzzer
// // // //   digitalWrite(redLED,  currentStatus == "TOO CLOSE");
// // // //   digitalWrite(greenLED, currentStatus == "EMPTY SPOT");
// // // //   digitalWrite(buzzerPin, currentStatus == "TOO CLOSE");

// // // //   // Send PARK message only when occupancy flips
// // // //   if (nowOccupied != lastOccupied) {
// // // //     lastOccupied = nowOccupied;
// // // //     spotsLeft   += nowOccupied ? -1 : 1;

// // // //     comm.print("PARK,");
// // // //     comm.print(nowOccupied ? 1 : 0);
// // // //     comm.print(",");
// // // //     comm.println(spotsLeft);
// // // //   }
// // // // }

// // // #include <LiquidCrystal.h>
// // // #include <SoftwareSerial.h>

// // // // LCD pins
// // // const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// // // LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// // // // Ultrasonic + LEDs + buzzer
// // // #define trigPin    6
// // // #define echoPin    7
// // // #define redLED     8
// // // #define yellowLED  9
// // // #define greenLED   10
// // // #define buzzerPin  13

// // // // SoftwareSerial: RX on 2, TX on 3
// // // SoftwareSerial comm(2, 3);

// // // unsigned long prevMillis        = 0;
// // // unsigned long prevSensorMillis  = 0;
// // // unsigned long lastSendMillis    = 0;
// // // const unsigned long blinkInterval  = 500;  // blink timing
// // // const unsigned long sensorInterval = 50;   // sensor read
// // // const unsigned long sendInterval   = 5000; // send to BSMS

// // // String currentStatus = "";
// // // String lastStatus    = "";
// // // bool   lastOccupied  = false;
// // // int    spotsLeft     = 10;

// // // void setup() {
// // //   lcd.begin(16, 2);
// // //   lcd.clear();

// // //   pinMode(redLED, OUTPUT);
// // //   pinMode(yellowLED, OUTPUT);
// // //   pinMode(greenLED, OUTPUT);
// // //   pinMode(buzzerPin, OUTPUT);

// // //   pinMode(trigPin, OUTPUT);
// // //   pinMode(echoPin, INPUT);

// // //   comm.begin(9600);
// // // }

// // // void loop() {
// // //   unsigned long now = millis();

// // //   if (now - prevSensorMillis >= sensorInterval) {
// // //     prevSensorMillis = now;
// // //     measureDistance();
// // //   }

// // //   // If "TOO CLOSE", blink red LED
// // //   if (currentStatus == "TOO CLOSE" && (now - prevMillis >= blinkInterval)) {
// // //     prevMillis = now;
// // //     digitalWrite(redLED, !digitalRead(redLED));  // Blink red
// // //   } else if (currentStatus != "TOO CLOSE") {
// // //     digitalWrite(redLED, LOW); // Solid red handled elsewhere
// // //   }

// // //   if (now - lastSendMillis >= sendInterval) {
// // //     lastSendMillis = now;
// // //     sendParkingStatus();
// // //   }
// // // }

// // // void measureDistance() {
// // //   digitalWrite(trigPin, LOW);
// // //   delayMicroseconds(2);
// // //   digitalWrite(trigPin, HIGH);
// // //   delayMicroseconds(10);
// // //   digitalWrite(trigPin, LOW);

// // //   long duration = pulseIn(echoPin, HIGH);
// // //   long distance = (duration / 2) / 30; // in cm

// // //   updateStatus(distance);
// // // }

// // // void updateStatus(long dist) {
// // //   bool nowOccupied;

// // //   if (dist < 10) {
// // //     currentStatus = "TOO CLOSE";
// // //     nowOccupied   = true;
// // //   }
// // //   else if (dist >= 10 && dist <= 20) {
// // //     currentStatus = "PERFECT POSITION";
// // //     nowOccupied   = true;
// // //   }
// // //   else {
// // //     currentStatus = "EMPTY SPOT";
// // //     nowOccupied   = false;
// // //   }

// // //   // Update LCD if status changed
// // //   if (currentStatus != lastStatus) {
// // //     lastStatus = currentStatus;
// // //     lcd.clear();
// // //     lcd.setCursor(0, 1);
// // //     lcd.print(currentStatus);
// // //   }

// // //   lcd.setCursor(0, 0);
// // //   lcd.print("Dist: ");
// // //   lcd.print(dist);
// // //   lcd.print(" cm   ");

// // //   // LEDs and buzzer behavior
// // //   if (currentStatus == "TOO CLOSE") {
// // //     digitalWrite(greenLED, LOW);
// // //     digitalWrite(buzzerPin, HIGH);
// // //     // redLED will blink in loop()
// // //   }
// // //   else if (currentStatus == "PERFECT POSITION") {
// // //     digitalWrite(redLED, HIGH);    // Solid red
// // //     digitalWrite(greenLED, LOW);
// // //     digitalWrite(buzzerPin, LOW);
// // //   }
// // //   else if (currentStatus == "EMPTY SPOT") {
// // //     digitalWrite(redLED, LOW);
// // //     digitalWrite(greenLED, HIGH);  // Solid green
// // //     digitalWrite(buzzerPin, LOW);
// // //   }

// // //   // Update spotsLeft only when occupancy flips
// // //   if (nowOccupied != lastOccupied) {
// // //     lastOccupied = nowOccupied;
// // //     spotsLeft   += nowOccupied ? -1 : 1;
// // //   }
// // // }

// // // void sendParkingStatus() {
// // //   comm.print("PARK,");
// // //   comm.print(lastOccupied ? 1 : 0);
// // //   comm.print(",");
// // //   comm.print(spotsLeft);
// // //   comm.print(",");
// // //   comm.println(currentStatus);
// // // }



// // #include <LiquidCrystal.h>
// // #include <SoftwareSerial.h>

// // const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// // LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// // #define trigPin    6
// // #define echoPin    7
// // #define redLED     8
// // #define yellowLED  9
// // #define greenLED   10
// // #define buzzerPin  13

// // SoftwareSerial comm(0, 1);

// // unsigned long prevMillis        = 0;
// // unsigned long yellowBlinkMillis = 0;
// // unsigned long prevSensorMillis  = 0;
// // unsigned long lastSendMillis    = 0;
// // const unsigned long blinkInterval  = 500;
// // const unsigned long sensorInterval = 50;
// // const unsigned long sendInterval   = 5000;

// // String currentStatus = "";
// // String lastStatus    = "";
// // bool   lastOccupied  = false;
// // int    spotsLeft     = 10;
// // int    lastDist      = 0;

// // void setup() {
// //   lcd.begin(16, 2);
// //   lcd.clear();

// //   pinMode(redLED, OUTPUT);
// //   pinMode(yellowLED, OUTPUT);
// //   pinMode(greenLED, OUTPUT);
// //   pinMode(buzzerPin, OUTPUT);

// //   pinMode(trigPin, OUTPUT);
// //   pinMode(echoPin, INPUT);

// //   comm.begin(9600);
// // }

// // void loop() {
// //   unsigned long now = millis();

// //   if (now - prevSensorMillis >= sensorInterval) {
// //     prevSensorMillis = now;
// //     measureDistance();
// //   }

// //   if (now - lastSendMillis >= sendInterval) {
// //     lastSendMillis = now;
// //     sendFullParkingReport();
// //   }
// // }

// // void measureDistance() {
// //   digitalWrite(trigPin, LOW);
// //   delayMicroseconds(2);
// //   digitalWrite(trigPin, HIGH);
// //   delayMicroseconds(10);
// //   digitalWrite(trigPin, LOW);

// //   long duration = pulseIn(echoPin, HIGH);
// //   long dist = (duration / 2) / 30;

// //   // Blink yellow if distance is fluctuating in 10–20 cm range
// //   if (dist >= 10 && dist <= 20 && abs(dist - lastDist) >= 2) {
// //     if (millis() - yellowBlinkMillis >= blinkInterval) {
// //       yellowBlinkMillis = millis();
// //       digitalWrite(yellowLED, !digitalRead(yellowLED));
// //     }
// //   } else {
// //     digitalWrite(yellowLED, LOW);
// //   }

// //   lastDist = dist;
// //   updateStatus(dist);
// // }

// // void updateStatus(long dist) {
// //   bool nowOccupied;

// //   if (dist < 10) {
// //     currentStatus = "TOO CLOSE";
// //     nowOccupied   = true;
// //   }
// //   else if (dist >= 10 && dist <= 20) {
// //     currentStatus = "PERFECT POSITION";
// //     nowOccupied   = true;
// //   }
// //   else {
// //     currentStatus = "EMPTY SPOT";
// //     nowOccupied   = false;
// //   }

// //   if (currentStatus != lastStatus) {
// //     lastStatus = currentStatus;
// //     lcd.clear();
// //     lcd.setCursor(0, 1);
// //     lcd.print(currentStatus);
// //   }

// //   lcd.setCursor(0, 0);
// //   lcd.print("Dist: ");
// //   lcd.print(dist);
// //   lcd.print(" cm   ");

// //   if (currentStatus == "TOO CLOSE") {
// //     digitalWrite(greenLED, LOW);
// //     digitalWrite(buzzerPin, HIGH);
// //   }
// //   else if (currentStatus == "PERFECT POSITION") {
// //     digitalWrite(redLED, HIGH);
// //     digitalWrite(greenLED, LOW);
// //     digitalWrite(buzzerPin, LOW);
// //   }
// //   else {
// //     digitalWrite(redLED, LOW);
// //     digitalWrite(greenLED, HIGH);
// //     digitalWrite(buzzerPin, LOW);
// //   }

// //   if (nowOccupied != lastOccupied) {
// //     lastOccupied = nowOccupied;
// //     spotsLeft += nowOccupied ? -1 : 1;
// //   }
// // }

// // void sendFullParkingReport() {
// //   comm.println("PARKING SPOT UPDATE:");
// //   comm.print("SPOTS LEFT: ");
// //   comm.println(spotsLeft);
// //   comm.print("SPOT 1 STATUS: ");
// //   comm.println(currentStatus);
// //   comm.println("END"); // to help BSMS detect when report ends
// // }

// #include <LiquidCrystal.h>
// #include <SoftwareSerial.h>

// const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// #define trigPin    6
// #define echoPin    7
// #define redLED     8
// #define yellowLED  9
// #define greenLED   10
// #define buzzerPin  13

// SoftwareSerial comm(0, 1);

// unsigned long prevMillis        = 0;
// unsigned long yellowBlinkMillis = 0;
// unsigned long prevSensorMillis  = 0;
// unsigned long lastSendMillis    = 0;
// const unsigned long blinkInterval  = 500;
// const unsigned long sensorInterval = 50;
// const unsigned long sendInterval   = 5000;

// String currentStatus = "";
// String lastStatus    = "";
// bool   lastOccupied  = false;
// int    spotsLeft     = 10;
// int    lastDist      = 0;

// void setup() {
//   lcd.begin(16, 2);
//   lcd.clear();

//   pinMode(redLED, OUTPUT);
//   pinMode(yellowLED, OUTPUT);
//   pinMode(greenLED, OUTPUT);
//   pinMode(buzzerPin, OUTPUT);

//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);

//   comm.begin(9600);
// }

// void loop() {
//   unsigned long now = millis();

//   if (now - prevSensorMillis >= sensorInterval) {
//     prevSensorMillis = now;
//     measureDistance();
//   }

//   if (now - lastSendMillis >= sendInterval) {
//     lastSendMillis = now;
//     sendFullParkingReport();
//   }
// }

// void measureDistance() {
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);

//   long duration = pulseIn(echoPin, HIGH);
//   long dist = (duration / 2) / 30;

//   if (dist >= 10 && dist <= 20 && abs(dist - lastDist) >= 2) {
//     if (millis() - yellowBlinkMillis >= blinkInterval) {
//       yellowBlinkMillis = millis();
//       digitalWrite(yellowLED, !digitalRead(yellowLED));
//     }
//   } else {
//     digitalWrite(yellowLED, LOW);
//   }

//   lastDist = dist;
//   updateStatus(dist);
// }

// void updateStatus(long dist) {
//   bool nowOccupied;

//   if (dist < 10) {
//     currentStatus = "TOO CLOSE";
//     nowOccupied   = true;
//   }
//   else if (dist >= 10 && dist <= 20) {
//     currentStatus = "PERFECT POSITION";
//     nowOccupied   = true;
//   }
//   else {
//     currentStatus = "EMPTY SPOT";
//     nowOccupied   = false;
//   }

//   if (currentStatus != lastStatus) {
//     lastStatus = currentStatus;
//     lcd.clear();
//     lcd.setCursor(0, 1);
//     lcd.print(currentStatus);
//   }

//   lcd.setCursor(0, 0);
//   lcd.print("Dist: ");
//   lcd.print(dist);
//   lcd.print(" cm   ");

//   if (currentStatus == "TOO CLOSE") {
//     digitalWrite(greenLED, LOW);
//     digitalWrite(buzzerPin, HIGH);
//   }
//   else if (currentStatus == "PERFECT POSITION") {
//     digitalWrite(redLED, HIGH);
//     digitalWrite(greenLED, LOW);
//     digitalWrite(buzzerPin, LOW);
//   }
//   else {
//     digitalWrite(redLED, LOW);
//     digitalWrite(greenLED, HIGH);
//     digitalWrite(buzzerPin, LOW);
//   }

//   if (nowOccupied != lastOccupied) {
//     lastOccupied = nowOccupied;
//     spotsLeft += nowOccupied ? -1 : 1;
//   }
// }

// void sendFullParkingReport() {
//   comm.println("PARKING SPOT UPDATE:");
//   comm.print("SPOTS LEFT: ");
//   comm.println(spotsLeft);
//   comm.print("SPOT 1 STATUS: ");
//   comm.println(currentStatus);
//   comm.println("END"); // Indicates report complete
// }



#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define trigPin    6
#define echoPin    7
#define redLED     8
#define yellowLED  9
#define greenLED   10
#define buzzerPin  13

SoftwareSerial comm(0, 1);

unsigned long prevMillis        = 0;
unsigned long yellowBlinkMillis = 0;
unsigned long prevSensorMillis  = 0;
unsigned long lastSendMillis    = 0;
const unsigned long blinkInterval  = 500;
const unsigned long sensorInterval = 50;
const unsigned long sendInterval   = 5000;

String currentStatus = "";
String lastStatus    = "";
bool   lastOccupied  = false;
int    spotsLeft     = 10;
int    lastDist      = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  comm.begin(9600);
}

void loop() {
  unsigned long now = millis();

  if (now - prevSensorMillis >= sensorInterval) {
    prevSensorMillis = now;
    measureDistance();
  }

  if (now - lastSendMillis >= sendInterval) {
    lastSendMillis = now;
    sendFullParkingReport();
  }
}

void measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // <--- ADDED TIMEOUT
  long dist = (duration / 2) / 30;

  // Blink yellow if distance is fluctuating
  if (dist >= 10 && dist <= 20 && abs(dist - lastDist) >= 2) {
    if (millis() - yellowBlinkMillis >= blinkInterval) {
      yellowBlinkMillis = millis();
      digitalWrite(yellowLED, !digitalRead(yellowLED));
    }
  } else {
    digitalWrite(yellowLED, LOW);
  }

  lastDist = dist;
  updateStatus(dist);
}

void updateStatus(long dist) {
  bool nowOccupied;

  if (dist < 10) {
    currentStatus = "TOO CLOSE";
    nowOccupied   = true;
  }
  else if (dist >= 10 && dist <= 30) {
    currentStatus = "PERFECT POSITION";
    nowOccupied   = true;
  }
  else {
    currentStatus = "EMPTY SPOT";
    nowOccupied   = false;
  }

  if (currentStatus != lastStatus) {
    lastStatus = currentStatus;
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(currentStatus);
  }

  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(dist);
  lcd.print(" cm   ");

  // Only buzz if TOO CLOSE
  if (currentStatus == "TOO CLOSE") {
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzerPin, HIGH);
  }
  else {
    digitalWrite(buzzerPin, LOW);
    if (currentStatus == "PERFECT POSITION") {
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
    }
    else {
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
    }
  }

  if (nowOccupied != lastOccupied) {
    lastOccupied = nowOccupied;
    spotsLeft += nowOccupied ? -1 : 1;
  }
}

void sendFullParkingReport() {
  comm.println("PARKING SPOT UPDATE:");
  comm.print("SPOTS LEFT: ");
  comm.println(spotsLeft);
  comm.print("SPOT 1 STATUS: ");
  comm.println(currentStatus);
  comm.println("END");
}
