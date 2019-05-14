#include "SR04.h"
#include "StateMachine.h"

#define TRIG_PIN 8
#define ECHO_PIN 9
#define RED_LED_PIN 6
#define AMBER_LED_PIN 5
#define GREEN_LED_PIN 3
#define SAMPLING_INTERVAL 250
#define SPEED_LIMIT 0.2 // m/s

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);

SmartTrafficLight stl = SmartTrafficLight(RED_LED_PIN, AMBER_LED_PIN, GREEN_LED_PIN);

long previousDistance = -1;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(AMBER_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  Serial.begin(9600);

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

    if (velocity > SPEED_LIMIT) {
      alarm(velocity);
    }
  }

  previousDistance = currentDistance;

  // Traffic light
  stl.update();

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
//  Serial.print("Alarm, speeding: ");
//  Serial.print(velocity);
//  Serial.println(" m/s");

  // Set traffic light to Red
  if (stl.getState().id == GO) {
    stl.setState(stateSlow);
  }

  Serial.print("Speeding,");
  Serial.println(velocity);
}
