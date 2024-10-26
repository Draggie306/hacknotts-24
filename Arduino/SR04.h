#ifndef SR04_H
#define SR04_H

#include <Arduino.h>

class SR04 {
  public:
    SR04(int echoPin, int trigPin);
    long Distance();
  
  private:
    int _echoPin;
    int _trigPin;
};

#endif