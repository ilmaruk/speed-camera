#include "TrafficLightItaly.h"

TrafficLightItaly::TrafficLightItaly(int redLedPin, int amberLedPin, int greenLedPin):
    TrafficLight(redLedPin, amberLedPin, greenLedPin) {
  State *states = new State[3] {
    State {GO, LOW, LOW, HIGH, 30000},
    State {SLOW, LOW, HIGH, LOW, 2500},
    State {STOP, HIGH, LOW, LOW, 30000},
  };
  init(states, 3);
}
