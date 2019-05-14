#include "StateMachine.h"

SmartTrafficLight::SmartTrafficLight(int redLedPin, int amberLedPin, int greenLedPin):
  redLedPin_(redLedPin), amberLedPin_(amberLedPin), greenLedPin_(greenLedPin) {
    setState(stateStop);
};

void SmartTrafficLight::update() {
  if (millis() >= nextStateAt_) {
    State nextState;
    switch (currentState_.id) {
      case STOP:
        nextState = stateReady;
        break;
      case READY:
        nextState = stateGo;
        break;
      case GO:
        nextState = stateSlow;
        break;
      case SLOW:
      default:
        nextState = stateStop;
        break;        
    }
    setState(nextState);
  }
}

void SmartTrafficLight::setState(State newState) {
  Serial.print("Setting state: ");
  Serial.println(newState.id);
  currentState_ = newState;
  digitalWrite(redLedPin_, currentState_.red);
  digitalWrite(amberLedPin_, currentState_.amber);
  digitalWrite(greenLedPin_, currentState_.green);
  nextStateAt_ = millis() + currentState_.duration;
}

State SmartTrafficLight::getState() {
  return currentState_;
}
