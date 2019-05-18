#ifndef TRAFFIC_LIGHT_ITA_H
#define TRAFFIC_LIGHT_ITA_H

#include "TrafficLight.h"

//
// The UK specific traffic light implementation.
//
class TrafficLightItaly: public TrafficLight {
public:
  TrafficLightItaly(int redLedPin, int amberLedPin, int greenLedPin);
};

#endif // TRAFFIC_LIGHT_ITA_H
