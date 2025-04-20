#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
private:
  int pin;
  bool isActive;

public:
  Buzzer(int buzzPin) : pin(buzzPin), isActive(false) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  
  void turnOn() {
    digitalWrite(pin, HIGH);
    isActive = true;
  }
  
  void turnOff() {
    digitalWrite(pin, LOW);
    isActive = false;
  }
  
  void beep(unsigned long duration) {
    turnOn();
    delay(duration);
    turnOff();
  }
  
  bool isOn() const {
    return isActive;
  }
};

#endif 