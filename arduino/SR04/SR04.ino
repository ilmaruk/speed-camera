//www.elegoo.com
//2016.12.08
#include "SR04.h"

#define TRIG_PIN 12
#define ECHO_PIN 11
#define LED 9
#define SAMPLING_INTERVAL 250
#define SPEED_LIMIT 1.0 // m/s

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);

long previousDistance = -1;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  sr04 = SR04(ECHO_PIN, TRIG_PIN);

  delay(1000);
}

void loop() {
  long currentDistance = sr04.Distance();
  //logValue("Distance", currentDistance, "mm");

  if (previousDistance != -1) {
    double movement = previousDistance - currentDistance;
    //logValue("Movement", movement, "mm");

    double velocity = movement / SAMPLING_INTERVAL; // mm/ms = m/s
    //logValue("Velocity", velocity, "m/s");

    Serial.print("Prev Dist: ");
    Serial.print(previousDistance);
    Serial.print("mm - Curr Dist: ");
    Serial.print(currentDistance);
    Serial.print("mm - Movement: ");
    Serial.print(movement);
    Serial.print("mm - Velocity: ");
    Serial.print(velocity);
    Serial.println("mm/ms");

    if (velocity > SPEED_LIMIT) {
      alarm(velocity);
    }
  }

  previousDistance = currentDistance;

  delay(SAMPLING_INTERVAL);
}

void logValue(const char *prefix, double value, const char *unit) {
  Serial.print(prefix);
  Serial.print(": ");
  Serial.print(value);
  Serial.print(" ");
  Serial.println(unit);
}

void alarm(double velocity) {
  Serial.print("Alarm, speeding: ");
  Serial.print(velocity);
  Serial.println(" m/s");

  // Turn on LED for 1 second
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);

  // TODO: notify RaspberryPi
}
