#include "DHT.h"

// Pin Assignments
#define LDR_PIN A0
#define DHT_PIN 2
#define GARDEN_LED 5
#define STAIR_LED 6
#define TRIG_PIN 9
#define ECHO_PIN 10

// Thresholds
#define DHTTYPE DHT22
#define LUX_THRESHOLD 500  // Wokwi LDR uses Lux-based simulation
#define DIST_THRESHOLD 100 // Detect human within 100cm

DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(GARDEN_LED, OUTPUT);
  pinMode(STAIR_LED, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  dht.begin();
  Serial.println("Smart Home System Starting...");
}

void loop() {
  // --- GARDEN LIGHT LOGIC (LDR) ---
  // In Wokwi, analogRead(A0) returns higher values for more light.
  int ldrValue = analogRead(LDR_PIN);
  if (ldrValue < LUX_THRESHOLD) { 
    digitalWrite(GARDEN_LED, HIGH); // Turn on when dark
  } else {
    digitalWrite(GARDEN_LED, LOW);
  }

  // --- STAIRCASE LIGHT LOGIC (Ultrasonic) ---
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  if (distance > 0 && distance < DIST_THRESHOLD) {
    digitalWrite(STAIR_LED, HIGH); // Human detected!
  } else {
    digitalWrite(STAIR_LED, LOW);
  }

  // --- ENVIRONMENT MONITORING (DHT22) ---
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Print to Serial Monitor for Debugging
  Serial.print("LDR: "); Serial.print(ldrValue);
  Serial.print(" | Dist: "); Serial.print(distance);
  Serial.print("cm | Temp: "); Serial.print(temp);
  Serial.println("C");

  delay(500); // Wait half a second before next check
}
