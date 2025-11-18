


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
