#include "SR04.h"

SR04::SR04(int echoPin, int trigPin) {
  _echoPin = echoPin;
  _trigPin = trigPin;
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

long SR04::Distance() {
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
  
  long duration = pulseIn(_echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  
  return distance;
}