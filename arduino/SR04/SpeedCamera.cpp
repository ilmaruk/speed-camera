#include "SpeedCamera.h"

SpeedCamera::SpeedCamera(SR04 sensor): sensor_(sensor), speedLimit_(speedLimit),
  previousDistance_(-1) {};

bool SpeedCamera::detectSpeeding(unsigned int samplingInterval) {
  long currentDistance = sensor_.Distance();

  bool alarm = false;
  if (previousDistance_ != -1) {
    double movement = previousDistance_ - currentDistance;
    currentVelocity_ = movement / samplingInterval; // mm/ms = m/s
    alarm = currentVelocity_ > speedLimit_;
  }

  previousDistance_ = currentDistance;
  return alarm;
}

double SpeedCamera::getVelocity() {
  return currentVelocity_;
}