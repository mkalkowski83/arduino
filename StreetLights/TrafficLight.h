#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

class TrafficLight {
  private:
    int redPin;
    int yellowPin;
    int greenPin;
    
  public:
    // Constructor
    TrafficLight(int red, int yellow, int green) {
      redPin = red;
      yellowPin = yellow;
      greenPin = green;
      
      // Initialize pins
      pinMode(redPin, OUTPUT);
      pinMode(yellowPin, OUTPUT);
      pinMode(greenPin, OUTPUT);
    }
    
    // Set all lights off
    void allOff() {
      digitalWrite(redPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(greenPin, LOW);
    }
    
    // Set red light on
    void turnOnRed() {
      digitalWrite(redPin, HIGH);
    }
    
    // Set yellow light on
    void turnOnYellow() {
      digitalWrite(yellowPin, HIGH);
    }
    
    // Set green light on
    void turnOnGreen() {
      digitalWrite(greenPin, HIGH);
    }
    
    // Blink a specific light (red, yellow, or green)
    void blinkLight(int pin, int times, int duration) {
      for (int i = 0; i < times; i++) {
        digitalWrite(pin, HIGH);
        delay(duration);
        digitalWrite(pin, LOW);
        delay(duration);
      }
    }
    
    // Blink green light
    void blinkGreen(int times, int duration) {
      blinkLight(greenPin, times, duration);
    }
    
    // Blink yellow light
    void blinkYellow(int times, int duration) {
      blinkLight(yellowPin, times, duration);
    }
};

#endif
