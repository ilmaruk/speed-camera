#ifndef STATE_MACHINE
#define STATE_MACHINE

#include <Arduino.h>

enum StateID { STOP, READY, GO, SLOW };

struct State {
  StateID id;
  int red;
  int amber;
  int green;
  unsigned int duration;
};

const State stateStop = {STOP, HIGH, LOW, LOW, 30000};
const State stateReady = {READY, HIGH, HIGH, LOW, 2500};
const State stateGo = {GO, LOW, LOW, HIGH, 30000};
const State stateSlow = {SLOW, LOW, HIGH, LOW, 2500};

class SmartTrafficLight {
public:
  SmartTrafficLight(int redLedPin, int amberLedPin, int greenLedPin);
  void update();
  void setState(State newState);
  State getState();
private:
  int redLedPin_;
  int amberLedPin_;
  int greenLedPin_;
  State currentState_;
  unsigned long nextStateAt_;
};

#endif
