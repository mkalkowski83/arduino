#ifndef BUTTON_H
#define BUTTON_H

class Button {
  private:
    int buttonPin;
    
  public:
    Button(int pin) {
      buttonPin = pin;
      pinMode(buttonPin, INPUT);
    }

    bool isPushed() {
      return digitalRead(buttonPin) == HIGH;
    }
};

#endif