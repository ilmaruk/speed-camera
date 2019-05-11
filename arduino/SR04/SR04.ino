//www.elegoo.com
//2016.12.08
#include "SR04.h"

#define TRIG_PIN 8
#define ECHO_PIN 9
#define RED 6
#define AMBER 5
#define GREEN 3
#define SAMPLING_INTERVAL 250
#define SPEED_LIMIT 0.2 // m/s

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);

long previousDistance = -1;

unsigned long nextStateAt = 0;
struct State {
  char id;
  int red;
  int amber;
  int green;
  unsigned int duration;
};
State state;
const State stateRed = {'r', HIGH, LOW, LOW, 30000};
const State stateAmber = {'a', LOW, HIGH, LOW, 2000};
const State stateGreen = {'g', LOW, LOW, HIGH, 60000};
const State stateGreenAmber = {'x', LOW, HIGH, HIGH, 3000};

#define STATE_RED = 

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(AMBER, OUTPUT);
  pinMode(GREEN, OUTPUT);
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

//    Serial.print("Prev Dist: ");
//    Serial.print(previousDistance);
//    Serial.print("mm - Curr Dist: ");
//    Serial.print(currentDistance);
//    Serial.print("mm - Movement: ");
//    Serial.print(movement);
//    Serial.print("mm - Velocity: ");
//    Serial.print(velocity);
//    Serial.println("mm/ms");

    if (velocity > SPEED_LIMIT) {
      alarm(velocity);
    }
  }

  previousDistance = currentDistance;

  // Traffic light
  if (nextStateAt == 0) {
    setState(stateRed);
  } else if (millis() >= nextStateAt) {
    switch (state.id) {
      case 'r':
        setState(stateAmber);
        break;
      case 'a':
        setState(stateGreen);
        break;
      case 'g':
        setState(stateGreenAmber);
        break;
      case 'x':
        setState(stateRed);
        break;
    }
  }

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
//  digitalWrite(RED, HIGH);
//  digitalWrite(AMBER, HIGH);
//  digitalWrite(GREEN, HIGH);
//  delay(1000);
//  digitalWrite(RED, LOW);
//  digitalWrite(AMBER, LOW);
//  digitalWrite(GREEN, LOW);

  // Set traffic light to Red
  if (state.id == 'g') {
    setState(stateGreenAmber);
  }

  // TODO: notify RaspberryPi
}

void setState(State nextState) {
  Serial.print("Setting state: ");
  Serial.println(nextState.id);
  state = nextState;
  digitalWrite(RED, state.red);
  digitalWrite(AMBER, state.amber);
  digitalWrite(GREEN, state.green);
  nextStateAt = millis() + state.duration;
}
