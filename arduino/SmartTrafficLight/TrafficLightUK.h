#ifndef TRAFFIC_LIGHT_UK_H
#define TRAFFIC_LIGHT_UK_H

#include "TrafficLight.h"

//
// The UK specific traffic light implementation.
//
class TrafficLightUK: public TrafficLight {
public:
  TrafficLightUK(int redLedPin, int amberLedPin, int greenLedPin);
};

#endif // TRAFFIC_LIGHT_UK_H
