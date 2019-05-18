#include "SR04.h"
#include "TrafficLightUK.h"
#include "SpeedCamera.h"

#define TRIG_PIN 8
#define ECHO_PIN 9
#define RED_LED_PIN 6
#define AMBER_LED_PIN 5
#define GREEN_LED_PIN 3
#define SAMPLING_INTERVAL 250
#define SPEED_LIMIT 0.2 // m/s

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);

TrafficLight tl = TrafficLightUK(RED_LED_PIN, AMBER_LED_PIN, GREEN_LED_PIN);

SpeedCamera sc = SpeedCamera(sr04, SPEED_LIMIT);

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(AMBER_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  Serial.begin(9600);

  tl.carousel();
}

void loop() {
  // Speed camera
  if (sc.detectSpeeding(SAMPLING_INTERVAL)) {
    alarm(sc.getVelocity());
  };

  // Traffic light
  tl.update();

  delay(SAMPLING_INTERVAL);
}

void alarm(double velocity) {
  // Set traffic light to Red
  if (tl.getState().id == GO) {
    tl.setState(SLOW); // This is wrong!!
  }

  Serial.print("Speeding,");
  Serial.println(velocity);
}
