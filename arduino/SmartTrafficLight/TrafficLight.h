#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <Arduino.h>

enum StateID { GO, STOP, SLOW, OTHER };

struct State {
  StateID id;
  int red;
  int amber;
  int green;
  unsigned int duration;
};

//
// A simple state-machine implementation to represent a generic traffic light.
//
class TrafficLight {
public:
  TrafficLight(int redLedPin, int amberLedPin, int greenLedPin);
  void update();
  void setState(int newStateIndex);
  void setState(StateID newStateID);
  State getState();
  void carousel();
protected:
  void init(State *states, int statesCount);
private:
  State *states_;
  int statesCount_;
  int redLedPin_;
  int amberLedPin_;
  int greenLedPin_;
  int currentStateIndex_;
  unsigned long nextStateAt_;
};

#endif // TRAFFIC_LIGHT_H
