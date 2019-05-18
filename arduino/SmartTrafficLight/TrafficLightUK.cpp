#include "TrafficLightUK.h"

TrafficLightUK::TrafficLightUK(int redLedPin, int amberLedPin, int greenLedPin):
    TrafficLight(redLedPin, amberLedPin, greenLedPin) {
  State *states = new State[4] {
    State {GO, LOW, LOW, HIGH, 30000},
    State {SLOW, LOW, HIGH, LOW, 2500},
    State {STOP, HIGH, LOW, LOW, 30000},
    State {OTHER, HIGH, HIGH, LOW, 2500},
  };
  init(states, 4);
}
