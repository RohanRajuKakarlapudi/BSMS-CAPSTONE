
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
