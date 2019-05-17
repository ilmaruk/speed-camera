#ifndef SPEED_CAMERA_H
#define SPEED_CAMERA_H

#include "SR04.h"

class SpeedCamera {
public:
    SpeedCamera(SR04 sensor, double speedLimit);
    bool detectSpeeding(unsigned int samplingInterval);
    double getVelocity();
private:
    SR04 sensor_;
    double speedLimit_;
    long previousDistance_;
    double currentVelocity_;
};

#endif //SPEED_CAMERA_H
