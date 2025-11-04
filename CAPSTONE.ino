

// // // // // // // // #include <Servo.h>

// // // // // // // // #define TRIGGER_PIN1        9
// // // // // // // // #define ECHO_PIN1           10
// // // // // // // // #define TRIGGER_PIN2        3
// // // // // // // // #define ECHO_PIN2           4
// // // // // // // // #define BUZZER_PIN          7
// // // // // // // // #define RED_LIGHT_PIN       11
// // // // // // // // #define YELLOW_LIGHT_PIN    6
// // // // // // // // #define GREEN_LIGHT_PIN     12
// // // // // // // // #define SERVO_PIN           6

// // // // // // // // unsigned long previousMillis    = 0;
// // // // // // // // unsigned long servoMillis       = 0;
// // // // // // // // unsigned long yellowLightMillis = 0;
// // // // // // // // unsigned long greenLightMillis  = 0;

// // // // // // // // const long interval           = 100;  // unused but kept for future
// // // // // // // // const long yellowInterval    = 100;
// // // // // // // // const long greenInterval     = 500;  // unused but kept for reference
// // // // // // // // const long fastGreenInterval = 200;
// // // // // // // // const long servoInterval     = 500;

// // // // // // // // Servo myservo;
// // // // // // // // int   angle       = 0;
// // // // // // // // bool  yellowState = false;
// // // // // // // // bool  greenState  = false;

// // // // // // // // void setup() {
// // // // // // // //   myservo.attach(SERVO_PIN);
// // // // // // // //   pinMode(TRIGGER_PIN1, OUTPUT);
// // // // // // // //   pinMode(ECHO_PIN1, INPUT);
// // // // // // // //   pinMode(TRIGGER_PIN2, OUTPUT);
// // // // // // // //   pinMode(ECHO_PIN2, INPUT);
// // // // // // // //   pinMode(BUZZER_PIN, OUTPUT);
// // // // // // // //   pinMode(RED_LIGHT_PIN, OUTPUT);
// // // // // // // //   pinMode(YELLOW_LIGHT_PIN, OUTPUT);
// // // // // // // //   pinMode(GREEN_LIGHT_PIN, OUTPUT);

// // // // // // // //   // start with all indicators off
// // // // // // // //   digitalWrite(RED_LIGHT_PIN, LOW);
// // // // // // // //   myservo.write(0);
// // // // // // // //   Serial.begin(9600);
// // // // // // // // }

// // // // // // // // void loop() {
// // // // // // // //   unsigned long currentMillis = millis();
// // // // // // // //   float duration1, distanceCm1, distanceInch1;
// // // // // // // //   float duration2, distanceCm2, distanceInch2;

// // // // // // // //   // ensure red LED is off by default
// // // // // // // //   digitalWrite(RED_LIGHT_PIN, LOW);

// // // // // // // //   // reset yellow LED state each cycle
// // // // // // // //   digitalWrite(YELLOW_LIGHT_PIN, LOW);
// // // // // // // //   yellowState = false;

// // // // // // // //   // ——— read first ultrasonic sensor ———
// // // // // // // //   digitalWrite(TRIGGER_PIN1, LOW);
// // // // // // // //   delayMicroseconds(2);
// // // // // // // //   digitalWrite(TRIGGER_PIN1, HIGH);
// // // // // // // //   delayMicroseconds(10);
// // // // // // // //   digitalWrite(TRIGGER_PIN1, LOW);
// // // // // // // //   duration1      = pulseIn(ECHO_PIN1, HIGH);
// // // // // // // //   distanceCm1    = (duration1 / 2) / 29.1;
// // // // // // // //   distanceInch1  = distanceCm1 * 0.393701;

// // // // // // // //   // ——— read second ultrasonic sensor ———
// // // // // // // //   digitalWrite(TRIGGER_PIN2, LOW);
// // // // // // // //   delayMicroseconds(2);
// // // // // // // //   digitalWrite(TRIGGER_PIN2, HIGH);
// // // // // // // //   delayMicroseconds(10);
// // // // // // // //   digitalWrite(TRIGGER_PIN2, LOW);
// // // // // // // //   duration2      = pulseIn(ECHO_PIN2, HIGH);
// // // // // // // //   distanceCm2    = (duration2 / 2) / 29.1;
// // // // // // // //   distanceInch2  = distanceCm2 * 0.393701;

// // // // // // // //   bool sensor1Triggered = (distanceInch1 <= 6);
// // // // // // // //   bool sensor2Triggered = (distanceInch2 <= 6);

// // // // // // // //   // ——— Condition 0: no objects ———
// // // // // // // //   if (!sensor1Triggered && !sensor2Triggered) {
// // // // // // // //     digitalWrite(GREEN_LIGHT_PIN, HIGH);  // solid green
// // // // // // // //     digitalWrite(BUZZER_PIN, LOW);
// // // // // // // //   }
// // // // // // // //   // ——— Condition 1: exactly one sensor ———
// // // // // // // //   else if (sensor1Triggered != sensor2Triggered) {
// // // // // // // //     digitalWrite(BUZZER_PIN, LOW);

// // // // // // // //     // faster blinking green
// // // // // // // //     if (currentMillis - greenLightMillis >= fastGreenInterval) {
// // // // // // // //       greenLightMillis = currentMillis;
// // // // // // // //       greenState       = !greenState;
// // // // // // // //       digitalWrite(GREEN_LIGHT_PIN, greenState ? HIGH : LOW);
// // // // // // // //     }
// // // // // // // //   }
// // // // // // // //   // ——— Condition 2: both sensors ———
// // // // // // // //   else if (sensor1Triggered && sensor2Triggered) {
// // // // // // // //     digitalWrite(RED_LIGHT_PIN, HIGH);     // turn red on
// // // // // // // //     digitalWrite(GREEN_LIGHT_PIN, LOW);
// // // // // // // //     digitalWrite(BUZZER_PIN, HIGH);
// // // // // // // //     Serial.println("CRASH DETECTED");

// // // // // // // //     // blinking yellow
// // // // // // // //     if (currentMillis - yellowLightMillis >= yellowInterval) {
// // // // // // // //       yellowLightMillis = currentMillis;
// // // // // // // //       yellowState       = !yellowState;
// // // // // // // //       digitalWrite(YELLOW_LIGHT_PIN, yellowState ? HIGH : LOW);
// // // // // // // //     }
// // // // // // // //   }

// // // // // // // //   // ——— servo oscillation ———
// // // // // // // //   if (currentMillis - servoMillis >= servoInterval) {
// // // // // // // //     servoMillis = currentMillis;
// // // // // // // //     angle       = (angle == 0) ? 90 : 0;
// // // // // // // //     myservo.write(angle);
// // // // // // // //   }
// // // // // // // // }




// // // // // // // // ------ Blind Spot Management System (BSMS) ------
// // // // // // // #include <Servo.h>
// // // // // // // #include <SoftwareSerial.h>

// // // // // // // #define TRIGGER_PIN1     9
// // // // // // // #define ECHO_PIN1       10
// // // // // // // #define TRIGGER_PIN2     3
// // // // // // // #define ECHO_PIN2        4
// // // // // // // #define BUZZER_PIN       7
// // // // // // // #define RED_LIGHT_PIN   11
// // // // // // // #define YELLOW_LIGHT_PIN 6
// // // // // // // #define GREEN_LIGHT_PIN 12
// // // // // // // #define SERVO_PIN        6

// // // // // // // Servo myservo;

// // // // // // // // comm from Parking: RX on 4, TX on 5
// // // // // // // SoftwareSerial comm(0, 1);

// // // // // // // unsigned long previousMillis    = 0;
// // // // // // // unsigned long servoMillis       = 0;
// // // // // // // unsigned long yellowLightMillis = 0;
// // // // // // // unsigned long greenLightMillis  = 0;

// // // // // // // const long yellowInterval    = 100;
// // // // // // // const long fastGreenInterval = 200;
// // // // // // // const long servoInterval     = 500;

// // // // // // // int   angle       = 0;
// // // // // // // bool  yellowState = false;
// // // // // // // bool  greenState  = false;

// // // // // // // void setup() {
// // // // // // //   // Servo & pins
// // // // // // //   myservo.attach(SERVO_PIN);
// // // // // // //   pinMode(TRIGGER_PIN1, OUTPUT);
// // // // // // //   pinMode(ECHO_PIN1, INPUT);
// // // // // // //   pinMode(TRIGGER_PIN2, OUTPUT);
// // // // // // //   pinMode(ECHO_PIN2, INPUT);
// // // // // // //   pinMode(BUZZER_PIN, OUTPUT);
// // // // // // //   pinMode(RED_LIGHT_PIN, OUTPUT);
// // // // // // //   pinMode(YELLOW_LIGHT_PIN, OUTPUT);
// // // // // // //   pinMode(GREEN_LIGHT_PIN, OUTPUT);

// // // // // // //   digitalWrite(RED_LIGHT_PIN, LOW);
// // // // // // //   myservo.write(0);

// // // // // // //   // comms
// // // // // // //   comm.begin(9600);
// // // // // // //   Serial.begin(9600);
// // // // // // // }

// // // // // // // void loop() {
// // // // // // //   unsigned long currentMillis = millis();

// // // // // // //   // Default off
// // // // // // //   digitalWrite(RED_LIGHT_PIN, LOW);
// // // // // // //   digitalWrite(YELLOW_LIGHT_PIN, LOW);
// // // // // // //   yellowState = false;

// // // // // // //   // Read sensor 1
// // // // // // //   digitalWrite(TRIGGER_PIN1, LOW);
// // // // // // //   delayMicroseconds(2);
// // // // // // //   digitalWrite(TRIGGER_PIN1, HIGH);
// // // // // // //   delayMicroseconds(10);
// // // // // // //   digitalWrite(TRIGGER_PIN1, LOW);
// // // // // // //   float duration1     = pulseIn(ECHO_PIN1, HIGH);
// // // // // // //   float distCm1       = (duration1 / 2) / 29.1;
// // // // // // //   float distInch1     = distCm1 * 0.393701;

// // // // // // //   // Read sensor 2
// // // // // // //   digitalWrite(TRIGGER_PIN2, LOW);
// // // // // // //   delayMicroseconds(2);
// // // // // // //   digitalWrite(TRIGGER_PIN2, HIGH);
// // // // // // //   delayMicroseconds(10);
// // // // // // //   digitalWrite(TRIGGER_PIN2, LOW);
// // // // // // //   float duration2     = pulseIn(ECHO_PIN2, HIGH);
// // // // // // //   float distCm2       = (duration2 / 2) / 29.1;
// // // // // // //   float distInch2     = distCm2 * 0.393701;

// // // // // // //   bool sensor1Triggered = (distInch1 <= 6);
// // // // // // //   bool sensor2Triggered = (distInch2 <= 6);

// // // // // // //   // Condition 0: no objects
// // // // // // //   if (!sensor1Triggered && !sensor2Triggered) {
// // // // // // //     digitalWrite(GREEN_LIGHT_PIN, HIGH);
// // // // // // //     digitalWrite(BUZZER_PIN, LOW);
// // // // // // //   }
// // // // // // //   // Condition 1: one sensor
// // // // // // //   else if (sensor1Triggered != sensor2Triggered) {
// // // // // // //     digitalWrite(BUZZER_PIN, LOW);
// // // // // // //     if (currentMillis - greenLightMillis >= fastGreenInterval) {
// // // // // // //       greenLightMillis = currentMillis;
// // // // // // //       greenState       = !greenState;
// // // // // // //       digitalWrite(GREEN_LIGHT_PIN, greenState ? HIGH : LOW);
// // // // // // //     }
// // // // // // //   }
// // // // // // //   // Condition 2: both sensors
// // // // // // //   else if (sensor1Triggered && sensor2Triggered) {
// // // // // // //     digitalWrite(RED_LIGHT_PIN, HIGH);
// // // // // // //     digitalWrite(GREEN_LIGHT_PIN, LOW);
// // // // // // //     digitalWrite(BUZZER_PIN, HIGH);
// // // // // // //     // Serial.println("CRASH DETECTED"); // commented out
// // // // // // //     if (currentMillis - yellowLightMillis >= yellowInterval) {
// // // // // // //       yellowLightMillis = currentMillis;
// // // // // // //       yellowState       = !yellowState;
// // // // // // //       digitalWrite(YELLOW_LIGHT_PIN, yellowState ? HIGH : LOW);
// // // // // // //     }
// // // // // // //   }

// // // // // // //   // Servo oscillation
// // // // // // //   if (currentMillis - servoMillis >= servoInterval) {
// // // // // // //     servoMillis = currentMillis;
// // // // // // //     angle       = (angle == 0) ? 90 : 0;
// // // // // // //     myservo.write(angle);
// // // // // // //   }

// // // // // // //   // Receive from Parking board
// // // // // // //   if (comm.available()) {
// // // // // // //     String msg = comm.readStringUntil('\n');
// // // // // // //     msg.trim();
// // // // // // //     if (msg.startsWith("PARK")) {
// // // // // // //       int idx1 = msg.indexOf(',');
// // // // // // //       int idx2 = msg.indexOf(',', idx1 + 1);
// // // // // // //       int occ  = msg.substring(idx1 + 1, idx2).toInt();
// // // // // // //       int left = msg.substring(idx2 + 1).toInt();
// // // // // // //       Serial.print("Spots left: ");
// // // // // // //       Serial.println(left);
// // // // // // //     }
// // // // // // //   }
// // // // // // // }


// // // // // // // ------ Blind Spot Management System (BSMS) ------
// // // // // // #include <Servo.h>
// // // // // // #include <SoftwareSerial.h>

// // // // // // #define TRIGGER_PIN1      9
// // // // // // #define ECHO_PIN1        10
// // // // // // #define TRIGGER_PIN2      3
// // // // // // #define ECHO_PIN2         4
// // // // // // #define BUZZER_PIN        7
// // // // // // #define RED_LIGHT_PIN    11
// // // // // // #define YELLOW_LIGHT_PIN  6
// // // // // // #define GREEN_LIGHT_PIN  12
// // // // // // #define SERVO_PIN         6

// // // // // // Servo myservo;

// // // // // // // comm from Parking: RX on 4, TX on 5
// // // // // // SoftwareSerial comm(0, 1);

// // // // // // unsigned long previousMillis      = 0;
// // // // // // unsigned long servoMillis         = 0;
// // // // // // unsigned long yellowLightMillis   = 0;
// // // // // // unsigned long greenLightMillis    = 0;
// // // // // // unsigned long crashStartMillis    = 0;

// // // // // // const long yellowInterval     = 100;
// // // // // // const long fastGreenInterval  = 200;
// // // // // // const long servoInterval      = 500;
// // // // // // const long crashThresholdMs   = 10000;  // 10 seconds

// // // // // // int   angle             = 0;
// // // // // // bool  yellowState       = false;
// // // // // // bool  greenState        = false;
// // // // // // bool  crashTimerRunning = false;
// // // // // // bool  crashWarned       = false;

// // // // // // void setup() {
// // // // // //   myservo.attach(SERVO_PIN);
// // // // // //   pinMode(TRIGGER_PIN1, OUTPUT);
// // // // // //   pinMode(ECHO_PIN1, INPUT);
// // // // // //   pinMode(TRIGGER_PIN2, OUTPUT);
// // // // // //   pinMode(ECHO_PIN2, INPUT);
// // // // // //   pinMode(BUZZER_PIN, OUTPUT);
// // // // // //   pinMode(RED_LIGHT_PIN, OUTPUT);
// // // // // //   pinMode(YELLOW_LIGHT_PIN, OUTPUT);
// // // // // //   pinMode(GREEN_LIGHT_PIN, OUTPUT);

// // // // // //   digitalWrite(RED_LIGHT_PIN, LOW);
// // // // // //   myservo.write(0);

// // // // // //   comm.begin(9600);
// // // // // //   Serial.begin(9600);
// // // // // // }

// // // // // // void loop() {
// // // // // //   unsigned long currentMillis = millis();

// // // // // //   // default off
// // // // // //   digitalWrite(RED_LIGHT_PIN, LOW);
// // // // // //   digitalWrite(YELLOW_LIGHT_PIN, LOW);
// // // // // //   yellowState = false;

// // // // // //   // read sensor 1
// // // // // //   digitalWrite(TRIGGER_PIN1, LOW);
// // // // // //   delayMicroseconds(2);
// // // // // //   digitalWrite(TRIGGER_PIN1, HIGH);
// // // // // //   delayMicroseconds(10);
// // // // // //   digitalWrite(TRIGGER_PIN1, LOW);
// // // // // //   float duration1 = pulseIn(ECHO_PIN1, HIGH);
// // // // // //   float distCm1   = (duration1 / 2) / 29.1;
// // // // // //   float distIn1   = distCm1 * 0.393701;

// // // // // //   // read sensor 2
// // // // // //   digitalWrite(TRIGGER_PIN2, LOW);
// // // // // //   delayMicroseconds(2);
// // // // // //   digitalWrite(TRIGGER_PIN2, HIGH);
// // // // // //   delayMicroseconds(10);
// // // // // //   digitalWrite(TRIGGER_PIN2, LOW);
// // // // // //   float duration2 = pulseIn(ECHO_PIN2, HIGH);
// // // // // //   float distCm2   = (duration2 / 2) / 29.1;
// // // // // //   float distIn2   = distCm2 * 0.393701;

// // // // // //   bool s1 = (distIn1 <= 6);
// // // // // //   bool s2 = (distIn2 <= 6);

// // // // // //   // Condition 0: no objects
// // // // // //   if (!s1 && !s2) {
// // // // // //     digitalWrite(GREEN_LIGHT_PIN, HIGH);
// // // // // //     digitalWrite(BUZZER_PIN, LOW);
// // // // // //   }
// // // // // //   // Condition 1: one sensor
// // // // // //   else if (s1 != s2) {
// // // // // //     digitalWrite(BUZZER_PIN, LOW);
// // // // // //     if (currentMillis - greenLightMillis >= fastGreenInterval) {
// // // // // //       greenLightMillis = currentMillis;
// // // // // //       greenState       = !greenState;
// // // // // //       digitalWrite(GREEN_LIGHT_PIN, greenState ? HIGH : LOW);
// // // // // //     }
// // // // // //   }
// // // // // //   // Condition 2: both sensors
// // // // // //   else if (s1 && s2) {
// // // // // //     digitalWrite(RED_LIGHT_PIN, HIGH);
// // // // // //     digitalWrite(GREEN_LIGHT_PIN, LOW);
// // // // // //     digitalWrite(BUZZER_PIN, HIGH);
// // // // // //     // Serial.println("CRASH DETECTED"); // commented out

// // // // // //     // blinking yellow
// // // // // //     if (currentMillis - yellowLightMillis >= yellowInterval) {
// // // // // //       yellowLightMillis = currentMillis;
// // // // // //       yellowState       = !yellowState;
// // // // // //       digitalWrite(YELLOW_LIGHT_PIN, yellowState ? HIGH : LOW);
// // // // // //     }

// // // // // //     // crash-duration tracking
// // // // // //     if (!crashTimerRunning) {
// // // // // //       crashTimerRunning  = true;
// // // // // //       crashStartMillis   = currentMillis;
// // // // // //       crashWarned        = false;
// // // // // //     } else if (!crashWarned && (currentMillis - crashStartMillis >= crashThresholdMs)) {
// // // // // //       Serial.println("HALT ACTIVITIES around lot, POTENTIAL ACCIDENT");
// // // // // //       crashWarned = true;
// // // // // //     }
// // // // // //   } else {
// // // // // //     // reset crash timer when not in crash state
// // // // // //     crashTimerRunning = false;
// // // // // //     crashWarned       = false;
// // // // // //   }

// // // // // //   // servo oscillation
// // // // // //   if (currentMillis - servoMillis >= servoInterval) {
// // // // // //     servoMillis = currentMillis;
// // // // // //     angle       = (angle == 0) ? 90 : 0;
// // // // // //     myservo.write(angle);
// // // // // //   }

// // // // // //   // comm receive (unchanged)
// // // // // //   if (comm.available()) {
// // // // // //     String msg = comm.readStringUntil('\n');
// // // // // //     msg.trim();
// // // // // //     if (msg.startsWith("PARK")) {
// // // // // //       int idx1 = msg.indexOf(',');
// // // // // //       int idx2 = msg.indexOf(',', idx1 + 1);
// // // // // //       int occ  = msg.substring(idx1 + 1, idx2).toInt();
// // // // // //       int left = msg.substring(idx2 + 1).toInt();
// // // // // //       Serial.print("Spots left: ");
// // // // // //       Serial.println(left);
// // // // // //     }
// // // // // //   }
// // // // // // }

// // // // // #include <Servo.h>
// // // // // #include <SoftwareSerial.h>

// // // // // #define TRIGGER_PIN1      9
// // // // // #define ECHO_PIN1        10
// // // // // #define TRIGGER_PIN2      3
// // // // // #define ECHO_PIN2         4
// // // // // #define BUZZER_PIN        7
// // // // // #define RED_LIGHT_PIN    11
// // // // // #define YELLOW_LIGHT_PIN  6
// // // // // #define GREEN_LIGHT_PIN  12
// // // // // #define SERVO_PIN         6

// // // // // Servo myservo;

// // // // // // comm from Parking: RX on 0, TX on 1 (SoftwareSerial)
// // // // // SoftwareSerial comm(0, 1);

// // // // // unsigned long previousMillis      = 0;
// // // // // unsigned long servoMillis         = 0;
// // // // // unsigned long yellowLightMillis   = 0;
// // // // // unsigned long greenLightMillis    = 0;
// // // // // unsigned long crashStartMillis    = 0;
// // // // // unsigned long lastPrintMillis     = 0;

// // // // // const long yellowInterval     = 100;
// // // // // const long fastGreenInterval  = 200;
// // // // // const long servoInterval      = 500;
// // // // // const long crashThresholdMs   = 10000;  // 10 seconds
// // // // // const long printInterval      = 5000;   // 5 seconds

// // // // // int   angle             = 0;
// // // // // bool  yellowState       = false;
// // // // // bool  greenState        = false;
// // // // // bool  crashTimerRunning = false;
// // // // // bool  crashWarned       = false;

// // // // // // Parking Info
// // // // // int spotsLeft         = 10;
// // // // // String currentStatus  = "EMPTY SPOT";

// // // // // void setup() {
// // // // //   myservo.attach(SERVO_PIN);
// // // // //   pinMode(TRIGGER_PIN1, OUTPUT);
// // // // //   pinMode(ECHO_PIN1, INPUT);
// // // // //   pinMode(TRIGGER_PIN2, OUTPUT);
// // // // //   pinMode(ECHO_PIN2, INPUT);
// // // // //   pinMode(BUZZER_PIN, OUTPUT);
// // // // //   pinMode(RED_LIGHT_PIN, OUTPUT);
// // // // //   pinMode(YELLOW_LIGHT_PIN, OUTPUT);
// // // // //   pinMode(GREEN_LIGHT_PIN, OUTPUT);

// // // // //   digitalWrite(RED_LIGHT_PIN, LOW);
// // // // //   myservo.write(0);

// // // // //   comm.begin(9600);
// // // // //   Serial.begin(9600);
// // // // // }

// // // // // void loop() {
// // // // //   unsigned long currentMillis = millis();

// // // // //   digitalWrite(RED_LIGHT_PIN, LOW);
// // // // //   digitalWrite(YELLOW_LIGHT_PIN, LOW);
// // // // //   yellowState = false;

// // // // //   // Read sensors
// // // // //   digitalWrite(TRIGGER_PIN1, LOW);
// // // // //   delayMicroseconds(2);
// // // // //   digitalWrite(TRIGGER_PIN1, HIGH);
// // // // //   delayMicroseconds(10);
// // // // //   digitalWrite(TRIGGER_PIN1, LOW);
// // // // //   float duration1 = pulseIn(ECHO_PIN1, HIGH);
// // // // //   float distCm1   = (duration1 / 2) / 29.1;
// // // // //   float distIn1   = distCm1 * 0.393701;

// // // // //   digitalWrite(TRIGGER_PIN2, LOW);
// // // // //   delayMicroseconds(2);
// // // // //   digitalWrite(TRIGGER_PIN2, HIGH);
// // // // //   delayMicroseconds(10);
// // // // //   digitalWrite(TRIGGER_PIN2, LOW);
// // // // //   float duration2 = pulseIn(ECHO_PIN2, HIGH);
// // // // //   float distCm2   = (duration2 / 2) / 29.1;
// // // // //   float distIn2   = distCm2 * 0.393701;

// // // // //   bool s1 = (distIn1 <= 6);
// // // // //   bool s2 = (distIn2 <= 6);

// // // // //   if (!s1 && !s2) {
// // // // //     digitalWrite(GREEN_LIGHT_PIN, HIGH);
// // // // //     digitalWrite(BUZZER_PIN, LOW);
// // // // //     crashTimerRunning = false;
// // // // //     crashWarned       = false;
// // // // //   }
// // // // //   else if (s1 != s2) {
// // // // //     digitalWrite(BUZZER_PIN, LOW);
// // // // //     if (currentMillis - greenLightMillis >= fastGreenInterval) {
// // // // //       greenLightMillis = currentMillis;
// // // // //       greenState       = !greenState;
// // // // //       digitalWrite(GREEN_LIGHT_PIN, greenState ? HIGH : LOW);
// // // // //     }
// // // // //     crashTimerRunning = false;
// // // // //     crashWarned       = false;
// // // // //   }
// // // // //   else if (s1 && s2) {
// // // // //     digitalWrite(RED_LIGHT_PIN, HIGH);
// // // // //     digitalWrite(GREEN_LIGHT_PIN, LOW);
// // // // //     digitalWrite(BUZZER_PIN, HIGH);

// // // // //     if (currentMillis - yellowLightMillis >= yellowInterval) {
// // // // //       yellowLightMillis = currentMillis;
// // // // //       yellowState       = !yellowState;
// // // // //       digitalWrite(YELLOW_LIGHT_PIN, yellowState ? HIGH : LOW);
// // // // //     }

// // // // //     if (!crashTimerRunning) {
// // // // //       crashTimerRunning  = true;
// // // // //       crashStartMillis   = currentMillis;
// // // // //       crashWarned        = false;
// // // // //     }
// // // // //     else if (!crashWarned && (currentMillis - crashStartMillis >= crashThresholdMs)) {
// // // // //       Serial.println("HALT ACTIVITIES around lot, POTENTIAL ACCIDENT");
// // // // //       crashWarned = true;
// // // // //     }
// // // // //   }

// // // // //   // servo oscillation
// // // // //   if (currentMillis - servoMillis >= servoInterval) {
// // // // //     servoMillis = currentMillis;
// // // // //     angle       = (angle == 0) ? 90 : 0;
// // // // //     myservo.write(angle);
// // // // //   }

// // // // //   // receive from Parking
// // // // //   if (comm.available()) {
// // // // //     String msg = comm.readStringUntil('\n');
// // // // //     msg.trim();
// // // // //     if (msg.startsWith("PARK")) {
// // // // //       int idx1 = msg.indexOf(',');
// // // // //       int idx2 = msg.indexOf(',', idx1 + 1);
// // // // //       int idx3 = msg.indexOf(',', idx2 + 1);

// // // // //       int occ = msg.substring(idx1 + 1, idx2).toInt();
// // // // //       spotsLeft = msg.substring(idx2 + 1, idx3).toInt();
// // // // //       currentStatus = msg.substring(idx3 + 1);
// // // // //     }
// // // // //   }

// // // // //   // structured print every 5s
// // // // //   if (currentMillis - lastPrintMillis >= printInterval) {
// // // // //     lastPrintMillis = currentMillis;
// // // // //     Serial.println("---------------------------------");
// // // // //     Serial.println("Parking Status Update:");
// // // // //     Serial.print("Spots Left: ");
// // // // //     Serial.println(spotsLeft);
// // // // //     Serial.print("Current Status: ");
// // // // //     Serial.println(currentStatus);
// // // // //     Serial.println("---------------------------------");
// // // // //   }
// // // // // }



// // // // #include <Servo.h>
// // // // #include <SoftwareSerial.h>

// // // // #define TRIGGER_PIN1      9
// // // // #define ECHO_PIN1         10
// // // // #define TRIGGER_PIN2      3
// // // // #define ECHO_PIN2         4
// // // // #define BUZZER_PIN        7
// // // // #define RED_LIGHT_PIN     11
// // // // #define YELLOW_LIGHT_PIN  6
// // // // #define GREEN_LIGHT_PIN   12
// // // // #define SERVO_PIN         6

// // // // Servo myservo;
// // // // SoftwareSerial comm(0, 1);

// // // // unsigned long servoMillis         = 0;
// // // // unsigned long yellowLightMillis   = 0;
// // // // unsigned long greenLightMillis    = 0;
// // // // unsigned long crashStartMillis    = 0;
// // // // unsigned long lastPrintMillis     = 0;

// // // // const long yellowInterval     = 200;
// // // // const long fastGreenInterval  = 200;
// // // // const long servoInterval      = 500;
// // // // const long crashThresholdMs   = 4000;

// // // // int angle             = 0;
// // // // bool yellowState      = false;
// // // // bool greenState       = false;
// // // // bool crashTimerActive = false;
// // // // bool crashWarned      = false;

// // // // String parkingReport = "";
// // // // bool reportStarted = false;

// // // // void setup() {
// // // //   myservo.attach(SERVO_PIN);
// // // //   pinMode(TRIGGER_PIN1, OUTPUT);
// // // //   pinMode(ECHO_PIN1, INPUT);
// // // //   pinMode(TRIGGER_PIN2, OUTPUT);
// // // //   pinMode(ECHO_PIN2, INPUT);
// // // //   pinMode(BUZZER_PIN, OUTPUT);
// // // //   pinMode(RED_LIGHT_PIN, OUTPUT);
// // // //   pinMode(YELLOW_LIGHT_PIN, OUTPUT);
// // // //   pinMode(GREEN_LIGHT_PIN, OUTPUT);

// // // //   digitalWrite(RED_LIGHT_PIN, LOW);
// // // //   myservo.write(0);

// // // //   comm.begin(9600);
// // // //   Serial.begin(9600);
// // // // }

// // // // void loop() {
// // // //   unsigned long now = millis();

// // // //   // Sensor readings
// // // //   digitalWrite(TRIGGER_PIN1, LOW);
// // // //   delayMicroseconds(2);
// // // //   digitalWrite(TRIGGER_PIN1, HIGH);
// // // //   delayMicroseconds(10);
// // // //   digitalWrite(TRIGGER_PIN1, LOW);
// // // //   float duration1 = pulseIn(ECHO_PIN1, HIGH);
// // // //   float distCm1 = (duration1 / 2) / 29.1;

// // // //   digitalWrite(TRIGGER_PIN2, LOW);
// // // //   delayMicroseconds(2);
// // // //   digitalWrite(TRIGGER_PIN2, HIGH);
// // // //   delayMicroseconds(10);
// // // //   digitalWrite(TRIGGER_PIN2, LOW);
// // // //   float duration2 = pulseIn(ECHO_PIN2, HIGH);
// // // //   float distCm2 = (duration2 / 2) / 29.1;

// // // //   bool inRange1 = (distCm1 >= 1 && distCm1 <= 20);
// // // //   bool inRange2 = (distCm2 >= 1 && distCm2 <= 20);

// // // //   if (inRange1 && inRange2) {
// // // //     // Both sensors detect → CRASH DETECTION
// // // //     digitalWrite(RED_LIGHT_PIN, !digitalRead(RED_LIGHT_PIN));
// // // //     digitalWrite(BUZZER_PIN, HIGH);
// // // //     digitalWrite(GREEN_LIGHT_PIN, LOW);

// // // //     if (!crashTimerActive) {
// // // //       crashStartMillis = now;
// // // //       crashTimerActive = true;
// // // //       crashWarned = false;
// // // //     }
// // // //     else if (!crashWarned && (now - crashStartMillis >= crashThresholdMs)) {
// // // //       crashWarned = true;
// // // //     }
// // // //   }
// // // //   else if (inRange1 || inRange2) {
// // // //     // Only one sensor → Green Blinking
// // // //     digitalWrite(GREEN_LIGHT_PIN, !digitalRead(GREEN_LIGHT_PIN));
// // // //     digitalWrite(BUZZER_PIN, LOW);
// // // //     digitalWrite(RED_LIGHT_PIN, LOW);
// // // //     crashTimerActive = false;
// // // //     crashWarned = false;
// // // //   }
// // // //   else {
// // // //     // No object detected
// // // //     digitalWrite(GREEN_LIGHT_PIN, HIGH);
// // // //     digitalWrite(RED_LIGHT_PIN, LOW);
// // // //     digitalWrite(BUZZER_PIN, LOW);
// // // //     crashTimerActive = false;
// // // //     crashWarned = false;
// // // //   }

// // // //   // Servo movement
// // // //   if (now - servoMillis >= servoInterval) {
// // // //     servoMillis = now;
// // // //     angle = (angle == 0) ? 90 : 0;
// // // //     myservo.write(angle);
// // // //   }

// // // //   // Serial receive
// // // //   while (comm.available()) {
// // // //     String line = comm.readStringUntil('\n');
// // // //     line.trim();

// // // //     if (line.startsWith("PARKING SPOT UPDATE:")) {
// // // //       parkingReport = "";
// // // //       reportStarted = true;
// // // //     }

// // // //     if (reportStarted) {
// // // //       parkingReport += line + "\n";
// // // //     }

// // // //     if (line == "END") {
// // // //       reportStarted = false;

// // // //       // Append parking lot safety status
// // // //       parkingReport += "PARKING LOT SAFETY UPDATE: ";
// // // //       parkingReport += crashWarned ? "POTENTIAL ACCIDENT" : "ALL CLEAR";
// // // //       parkingReport += "\n";

// // // //       // Print the full report
// // // //       Serial.println("\n==============================");
// // // //       Serial.print(parkingReport);
// // // //       Serial.println("==============================");

// // // //       parkingReport = "";
// // // //     }
// // // //   }
// // // // }


// // // #include <Servo.h>
// // // #include <SoftwareSerial.h>

// // // #define TRIGGER_PIN1      9
// // // #define ECHO_PIN1         10
// // // #define TRIGGER_PIN2      3
// // // #define ECHO_PIN2         4
// // // #define BUZZER_PIN        7
// // // #define RED_LIGHT_PIN     11
// // // #define YELLOW_LIGHT_PIN  6
// // // #define GREEN_LIGHT_PIN   12
// // // #define SERVO_PIN         6

// // // Servo myservo;
// // // SoftwareSerial comm(0, 1);

// // // unsigned long servoMillis         = 0;
// // // unsigned long yellowLightMillis   = 0;
// // // unsigned long greenLightMillis    = 0;
// // // unsigned long crashStartMillis    = 0;
// // // unsigned long lastPrintMillis     = 0;

// // // const long yellowInterval     = 200;
// // // const long fastGreenInterval  = 200;
// // // const long servoInterval      = 500;
// // // const long crashThresholdMs   = 4000;

// // // int angle             = 0;
// // // bool yellowState      = false;
// // // bool greenState       = false;
// // // bool crashTimerActive = false;
// // // bool crashWarned      = false;

// // // String parkingReport = "";
// // // bool reportStarted = false;

// // // void setup() {
// // //   myservo.attach(SERVO_PIN);
// // //   pinMode(TRIGGER_PIN1, OUTPUT);
// // //   pinMode(ECHO_PIN1, INPUT);
// // //   pinMode(TRIGGER_PIN2, OUTPUT);
// // //   pinMode(ECHO_PIN2, INPUT);
// // //   pinMode(BUZZER_PIN, OUTPUT);
// // //   pinMode(RED_LIGHT_PIN, OUTPUT);
// // //   pinMode(YELLOW_LIGHT_PIN, OUTPUT);
// // //   pinMode(GREEN_LIGHT_PIN, OUTPUT);

// // //   digitalWrite(RED_LIGHT_PIN, LOW);
// // //   myservo.write(0);

// // //   comm.begin(9600);
// // //   Serial.begin(9600);
// // // }

// // // void loop() {
// // //   unsigned long now = millis();

// // //   // Sensor readings with timeout
// // //   digitalWrite(TRIGGER_PIN1, LOW);
// // //   delayMicroseconds(2);
// // //   digitalWrite(TRIGGER_PIN1, HIGH);
// // //   delayMicroseconds(10);
// // //   digitalWrite(TRIGGER_PIN1, LOW);
// // //   float duration1 = pulseIn(ECHO_PIN1, HIGH, 30000); // <--- ADDED TIMEOUT
// // //   float distCm1 = (duration1 / 2) / 29.1;

// // //   digitalWrite(TRIGGER_PIN2, LOW);
// // //   delayMicroseconds(2);
// // //   digitalWrite(TRIGGER_PIN2, HIGH);
// // //   delayMicroseconds(10);
// // //   digitalWrite(TRIGGER_PIN2, LOW);
// // //   float duration2 = pulseIn(ECHO_PIN2, HIGH, 30000); // <--- ADDED TIMEOUT
// // //   float distCm2 = (duration2 / 2) / 29.1;

// // //   bool inRange1 = (distCm1 >= 1 && distCm1 <= 20);
// // //   bool inRange2 = (distCm2 >= 1 && distCm2 <= 20);

// // //   if (inRange1 && inRange2) {
// // //     digitalWrite(RED_LIGHT_PIN, !digitalRead(RED_LIGHT_PIN));
// // //     digitalWrite(BUZZER_PIN, HIGH);
// // //     digitalWrite(GREEN_LIGHT_PIN, LOW);

// // //     if (!crashTimerActive) {
// // //       crashStartMillis = now;
// // //       crashTimerActive = true;
// // //       crashWarned = false;
// // //     }
// // //     else if (!crashWarned && (now - crashStartMillis >= crashThresholdMs)) {
// // //       crashWarned = true;
// // //     }
// // //   }
// // //   else if (inRange1 || inRange2) {
// // //     digitalWrite(GREEN_LIGHT_PIN, !digitalRead(GREEN_LIGHT_PIN));
// // //     digitalWrite(BUZZER_PIN, LOW);
// // //     digitalWrite(RED_LIGHT_PIN, LOW);
// // //     crashTimerActive = false;
// // //     crashWarned = false;
// // //   }
// // //   else {
// // //     digitalWrite(GREEN_LIGHT_PIN, HIGH);
// // //     digitalWrite(RED_LIGHT_PIN, LOW);
// // //     digitalWrite(BUZZER_PIN, LOW);
// // //     crashTimerActive = false;
// // //     crashWarned = false;
// // //   }

// // //   if (now - servoMillis >= servoInterval) {
// // //     servoMillis = now;
// // //     angle = (angle == 0) ? 90 : 0;
// // //     myservo.write(angle);
// // //   }

// // //   while (comm.available()) {
// // //     String line = comm.readStringUntil('\n');
// // //     line.trim();

// // //     if (line.startsWith("PARKING SPOT UPDATE:")) {
// // //       parkingReport = "";
// // //       reportStarted = true;
// // //     }

// // //     if (reportStarted) {
// // //       parkingReport += line + "\n";
// // //     }

// // //     if (line == "END") {
// // //       reportStarted = false;

// // //       parkingReport += "PARKING LOT SAFETY UPDATE: ";
// // //       parkingReport += crashWarned ? "POTENTIAL ACCIDENT" : "ALL CLEAR";
// // //       parkingReport += "\n";

// // //       Serial.println("\n==============================");
// // //       Serial.print(parkingReport);
// // //       Serial.println("==============================");

// // //       parkingReport = "";
// // //     }
// // //   }
// // // }


// // #include <Servo.h>
// // #include <SoftwareSerial.h>

// // #define TRIGGER_PIN1      9
// // #define ECHO_PIN1         10
// // #define TRIGGER_PIN2      3
// // #define ECHO_PIN2         4
// // #define BUZZER_PIN        7
// // #define RED_LIGHT_PIN     11
// // #define YELLOW_LIGHT_PIN  6
// // #define GREEN_LIGHT_PIN   12
// // #define SERVO_PIN         6

// // Servo myservo;
// // SoftwareSerial comm(0, 1);

// // unsigned long servoMillis      = 0;
// // unsigned long lastPrintMillis  = 0;

// // const long servoInterval      = 500;
// // const long printInterval      = 5000;

// // int angle             = 0;
// // bool crashDetected    = false;

// // String parkingReport  = "";
// // bool reportStarted    = false;

// // void setup() {
// //   myservo.attach(SERVO_PIN);
// //   pinMode(TRIGGER_PIN1, OUTPUT);
// //   pinMode(ECHO_PIN1, INPUT);
// //   pinMode(TRIGGER_PIN2, OUTPUT);
// //   pinMode(ECHO_PIN2, INPUT);
// //   pinMode(BUZZER_PIN, OUTPUT);
// //   pinMode(RED_LIGHT_PIN, OUTPUT);
// //   pinMode(YELLOW_LIGHT_PIN, OUTPUT);
// //   pinMode(GREEN_LIGHT_PIN, OUTPUT);

// //   digitalWrite(RED_LIGHT_PIN, LOW);
// //   myservo.write(0);

// //   comm.begin(9600);
// //   Serial.begin(9600);
// // }

// // void loop() {
// //   unsigned long now = millis();

// //   // Sensor readings with timeout
// //   float distCm1 = readUltrasonic(TRIGGER_PIN1, ECHO_PIN1);
// //   float distCm2 = readUltrasonic(TRIGGER_PIN2, ECHO_PIN2);

// //   bool inRange1 = (distCm1 >= 1 && distCm1 <= 20);
// //   bool inRange2 = (distCm2 >= 1 && distCm2 <= 20);

// //   if (inRange1 && inRange2) {
// //     crashDetected = true;
// //     digitalWrite(RED_LIGHT_PIN, HIGH);
// //     digitalWrite(BUZZER_PIN, HIGH);
// //     digitalWrite(GREEN_LIGHT_PIN, LOW);
// //   }
// //   else if (inRange1 || inRange2) {
// //     crashDetected = false;
// //     digitalWrite(GREEN_LIGHT_PIN, !digitalRead(GREEN_LIGHT_PIN)); // Blink green
// //     digitalWrite(RED_LIGHT_PIN, LOW);
// //     digitalWrite(BUZZER_PIN, LOW);
// //   }
// //   else {
// //     crashDetected = false;
// //     digitalWrite(GREEN_LIGHT_PIN, HIGH);  // Solid green
// //     digitalWrite(RED_LIGHT_PIN, LOW);
// //     digitalWrite(BUZZER_PIN, LOW);
// //   }

// //   // Servo movement
// //   if (now - servoMillis >= servoInterval) {
// //     servoMillis = now;
// //     angle = (angle == 0) ? 90 : 0;
// //     myservo.write(angle);
// //   }

// //   // Receive from Parking Spot Manager
// //   while (comm.available()) {
// //     String line = comm.readStringUntil('\n');
// //     line.trim();

// //     if (line.startsWith("PARKING SPOT UPDATE:")) {
// //       parkingReport = "";
// //       reportStarted = true;
// //     }

// //     if (reportStarted) {
// //       parkingReport += line + "\n";
// //     }

// //     if (line == "END") {
// //       reportStarted = false;

// //       parkingReport += "PARKING LOT SAFETY UPDATE: ";
// //       parkingReport += crashDetected ? "POTENTIAL ACCIDENT" : "ALL CLEAR";
// //       parkingReport += "\n";

// //       Serial.println("\n==============================");
// //       Serial.print(parkingReport);
// //       Serial.println("==============================");

// //       parkingReport = "";
// //     }
// //   }
// // }

// // // Utility function for ultrasonic with timeout
// // float readUltrasonic(int trigPin, int echoPin) {
// //   digitalWrite(trigPin, LOW);
// //   delayMicroseconds(2);
// //   digitalWrite(trigPin, HIGH);
// //   delayMicroseconds(10);
// //   digitalWrite(trigPin, LOW);

// //   long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
// //   if (duration == 0) return 1000; // Timeout → assume no object
// //   return (duration / 2) / 29.1;    // cm
// // }



// #include <Servo.h>
// #include <SoftwareSerial.h>

// #define TRIGGER_PIN1      9
// #define ECHO_PIN1         10
// #define TRIGGER_PIN2      3
// #define ECHO_PIN2         4
// #define BUZZER_PIN        7
// #define RED_LIGHT_PIN     11
// #define YELLOW_LIGHT_PIN  6
// #define GREEN_LIGHT_PIN   12
// #define SERVO_PIN         6

// Servo myservo;
// SoftwareSerial comm(0, 1);

// unsigned long servoMillis        = 0;
// unsigned long lastSensorMillis   = 0;
// unsigned long lastPrintMillis    = 0;

// const long servoInterval     = 500;
// const long sensorInterval    = 100;   // Read sensors every 100ms
// const long printInterval     = 5000;  // Print every 5 seconds

// bool crashDetected           = false;
// bool lastCrashState          = false;

// String parkingReport = "";
// bool reportStarted = false;

// void setup() {
//   myservo.attach(SERVO_PIN);
//   pinMode(TRIGGER_PIN1, OUTPUT);
//   pinMode(ECHO_PIN1, INPUT);
//   pinMode(TRIGGER_PIN2, OUTPUT);
//   pinMode(ECHO_PIN2, INPUT);
//   pinMode(BUZZER_PIN, OUTPUT);
//   pinMode(RED_LIGHT_PIN, OUTPUT);
//   pinMode(YELLOW_LIGHT_PIN, OUTPUT);
//   pinMode(GREEN_LIGHT_PIN, OUTPUT);

//   digitalWrite(RED_LIGHT_PIN, LOW);
//   myservo.write(0);

//   comm.begin(9600);
//   Serial.begin(9600);
// }

// void loop() {
//   unsigned long now = millis();

//   // ======== SENSOR READING FAST ========
//   if (now - lastSensorMillis >= sensorInterval) {
//     lastSensorMillis = now;

//     float dist1 = readUltrasonic(TRIGGER_PIN1, ECHO_PIN1);
//     float dist2 = readUltrasonic(TRIGGER_PIN2, ECHO_PIN2);

//     bool inRange1 = (dist1 >= 1 && dist1 <= 20);
//     bool inRange2 = (dist2 >= 1 && dist2 <= 20);

//     if (inRange1 && inRange2) {
//       crashDetected = true;
//       digitalWrite(RED_LIGHT_PIN, HIGH);
//       digitalWrite(BUZZER_PIN, HIGH);
//       digitalWrite(GREEN_LIGHT_PIN, LOW);
//     }
//     else if (inRange1 || inRange2) {
//       crashDetected = false;
//       digitalWrite(GREEN_LIGHT_PIN, !digitalRead(GREEN_LIGHT_PIN)); // Blinking green
//       digitalWrite(RED_LIGHT_PIN, LOW);
//       digitalWrite(BUZZER_PIN, LOW);
//     }
//     else {
//       crashDetected = false;
//       digitalWrite(GREEN_LIGHT_PIN, HIGH);
//       digitalWrite(RED_LIGHT_PIN, LOW);
//       digitalWrite(BUZZER_PIN, LOW);
//     }
//   }

//   // ======== SERVO MOVEMENT ========
//   if (now - servoMillis >= servoInterval) {
//     servoMillis = now;
//     static int angle = 0;
//     angle = (angle == 0) ? 90 : 0;
//     myservo.write(angle);
//   }

//   // ======== COMM RECEIVE (PARKING REPORT) ========
//   while (comm.available()) {
//     String line = comm.readStringUntil('\n');
//     line.trim();

//     if (line.startsWith("PARKING SPOT UPDATE:")) {
//       parkingReport = "";
//       reportStarted = true;
//     }

//     if (reportStarted) {
//       parkingReport += line + "\n";
//     }

//     if (line == "END") {
//       reportStarted = false;

//       // append safety update
//       parkingReport += "PARKING LOT SAFETY UPDATE: ";
//       parkingReport += crashDetected ? "POTENTIAL ACCIDENT" : "ALL CLEAR";
//       parkingReport += "\n";
//     }
//   }


// // ADD MORE DATA EXCHANGE, IMPORTANT ALERTS AND LOAD THESE
// // INTO A CSV FILE OR SOMETHING THAT COULD BE USED
// // BY SQL - BAKCEND 
//   // ======== EVERY 5 SECONDS, PRINT NO MATTER WHAT ========
//   if (now - lastPrintMillis >= printInterval) {
//     lastPrintMillis = now;

//     Serial.println("\n==============================");
//     Serial.print(parkingReport);
//     Serial.println("==============================");
//   }
// }

// // Non-blocking ultrasonic read
// float readUltrasonic(int trigPin, int echoPin) {
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);

//   long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
//   if (duration == 0) return 1000; // assume no object
//   return (duration / 2) / 29.1;
// }


#include <Servo.h>
#include <SoftwareSerial.h>

#define TRIGGER_PIN1      10
#define ECHO_PIN1         9
#define TRIGGER_PIN2      4
#define ECHO_PIN2         3
#define BUZZER_PIN        7
#define RED_LIGHT_PIN     11
#define YELLOW_LIGHT_PIN  6
#define GREEN_LIGHT_PIN   12
#define SERVO_PIN         6

Servo myservo;
SoftwareSerial comm(0, 1);  // RX on pin 0, TX on pin 1

unsigned long servoMillis        = 0;
unsigned long lastSensorMillis   = 0;
unsigned long lastPrintMillis    = 0;

const long servoInterval     = 500;
const long sensorInterval    = 100;
const long printInterval     = 5000;

bool crashDetected           = false;
String parkingReport         = "";
bool reportStarted           = false;

void setup() {
  myservo.attach(SERVO_PIN);
  pinMode(TRIGGER_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIGGER_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LIGHT_PIN, OUTPUT);
  pinMode(YELLOW_LIGHT_PIN, OUTPUT);
  pinMode(GREEN_LIGHT_PIN, OUTPUT);

  digitalWrite(RED_LIGHT_PIN, LOW);
  digitalWrite(GREEN_LIGHT_PIN, HIGH);
  myservo.write(0);

  comm.begin(9600);
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();

  // === SENSOR READING ===
  if (now - lastSensorMillis >= sensorInterval) {
    lastSensorMillis = now;

    float dist1 = readUltrasonic(TRIGGER_PIN1, ECHO_PIN1);
    float dist2 = readUltrasonic(TRIGGER_PIN2, ECHO_PIN2);

    bool inRange1 = (dist1 >= 1 && dist1 <= 20);
    bool inRange2 = (dist2 >= 1 && dist2 <= 20);

    if (inRange1 && inRange2) {
      crashDetected = true;
      digitalWrite(RED_LIGHT_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      digitalWrite(GREEN_LIGHT_PIN, LOW);
    }
    else if (inRange1 || inRange2) {
      crashDetected = false;
      digitalWrite(GREEN_LIGHT_PIN, !digitalRead(GREEN_LIGHT_PIN)); // blink
      digitalWrite(RED_LIGHT_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
    }
    else {
      crashDetected = false;
      digitalWrite(GREEN_LIGHT_PIN, HIGH);
      digitalWrite(RED_LIGHT_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
    }
  }

  // === SERVO OSCILLATION ===
  if (now - servoMillis >= servoInterval) {
    servoMillis = now;
    static int angle = 0;
    angle = (angle == 0) ? 90 : 0;
    myservo.write(angle);
  }

  // === COMM RECEIVE ===
  while (comm.available()) {
    String line = comm.readStringUntil('\n');
    line.trim();

    if (line.startsWith("PARKING SPOT UPDATE:")) {
      parkingReport = "";
      reportStarted = true;
    }

    if (reportStarted) {
      parkingReport += line + "\n";
    }

   if (line == "END") {
  reportStarted = false;
  parkingReport += "PARKING LOT SAFETY UPDATE: ";
  parkingReport += crashDetected ? "POTENTIAL ACCIDENT" : "ALL CLEAR";
  parkingReport += "\n==============================\n";

  // ✅ Immediately print full report so frontend sees it
  Serial.println("\n==============================");
  Serial.print(parkingReport);
  Serial.println("==============================");
}

  }

  // === STRUCTURED PRINTING EVERY 5s ===
  if (now - lastPrintMillis >= printInterval) {
    lastPrintMillis = now;
    Serial.println("\n==============================");
    Serial.print(parkingReport);
    Serial.println("==============================");
  }
}

float readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);  // timeout = 30ms
  if (duration == 0) return 1000; // timeout fallback
  return (duration / 2) / 29.1;
}
