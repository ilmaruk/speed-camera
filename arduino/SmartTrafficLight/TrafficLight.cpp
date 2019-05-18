#include "TrafficLight.h"

TrafficLight::TrafficLight(int redLedPin, int amberLedPin, int greenLedPin):
  redLedPin_(redLedPin), amberLedPin_(amberLedPin), greenLedPin_(greenLedPin) {};

void TrafficLight::init(State *states, int statesCount) {
  states_ = states;
  statesCount_ = statesCount;
  setState(0);
}

//
// Check whether it is time to move to the next state.
//
void TrafficLight::update() {
  if (millis() >= nextStateAt_) {
    int nextStateIndex = currentStateIndex_ + 1;
    if (nextStateIndex >= statesCount_) {
      nextStateIndex = 0;
    }
    setState(nextStateIndex);
  }
}

//
// Set the new state, given its index in the states list.
//
void TrafficLight::setState(int newStateIndex) {
  currentStateIndex_ = newStateIndex;
  State currentState = states_[currentStateIndex_];
  digitalWrite(redLedPin_, currentState.red);
  digitalWrite(amberLedPin_, currentState.amber);
  digitalWrite(greenLedPin_, currentState.green);
  nextStateAt_ = millis() + currentState.duration;
  Serial.print("State,");
  Serial.print(newStateIndex);
  Serial.print(",");
  Serial.print(currentState.red);
  Serial.print(",");
  Serial.print(currentState.amber);
  Serial.print(",");
  Serial.println(currentState.green);
}

//
// Set a new state given its identifier.
// NB: if there are more than one state with the same identifier,
// then the first one in the states list is selected.
//
void TrafficLight::setState(StateID newStateID) {
  int newStateIndex = 0;
  for (int i=0; i<statesCount_; i++) {
    if (states_[i].id == newStateID) {
      newStateIndex = i;
      break;
    }
  }
  setState(newStateIndex);
}

State TrafficLight::getState() {
  return states_[currentStateIndex_];
}

//
// Make a full loop 3 times, to confirm all LED's are
// working fine and the loop is correct.
//
void TrafficLight::carousel() {
  int pins[3] = {redLedPin_, amberLedPin_, greenLedPin_};
  int initialStateIndex = currentStateIndex_;

  // Turns all the LED's off
  for (int p=0; p<3; p++) {
    digitalWrite(pins[p], LOW);
  }

  // Now the proper carousel
  for (int i=0; i<3; i++) {
    for (int s=0; s<statesCount_; s++) {
      setState(s);
      delay(400);
    }
  }

  // Eventually back to the original state
  setState(initialStateIndex);
}
