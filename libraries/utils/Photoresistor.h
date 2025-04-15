#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

class Photoresistor {
  private:
    int analogPin;
  
  public:    
    Photoresistor(int pin) {
      analogPin = pin;      
    }
    
    float readValue() {
      return map(analogRead(analogPin), 0, 1023, 0, 100);
    }
};

#endif 