//www.elegoo.com
//2016.12.08
#include "SR04.h"

#define TRIG_PIN 12
#define ECHO_PIN 11
#define LED       9

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);

bool alarm = false;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  long d = sr04.Distance();
  Serial.print(d);
  Serial.println("mm");

  if (d < 100 && !alarm) {
    setAlarm(d);
  } else if (d>=100 && alarm) {
    resetAlarm();
  }

  delay(250);
}

void setAlarm(long d) {
  alarm = true;
  Serial.print("Alarm; distance is < 100mm: ");
  Serial.print(d);
  Serial.println("mm");
  analogWrite(led, HIGH);
}

void resetAlarm() {
  alarm = false;
  analogWrite(led, LOW);
}
