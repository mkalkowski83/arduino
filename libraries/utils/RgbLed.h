#ifndef RGB_LED_H
#define RGB_LED_H

class RgbLed {
  private:
    int redPin;
    int greenPin;
    int bluePin;
    
  public:
    // Constructor
    RgbLed(int red, int green, int blue) {
      redPin = red;
      bluePin = blue;
      greenPin = green;
      
      // Initialize pins
      pinMode(redPin, OUTPUT);
      pinMode(bluePin, OUTPUT);
      pinMode(greenPin, OUTPUT);
    }
    
    // Set all lights off
    void allOff() {
      digitalWrite(redPin, LOW);
      digitalWrite(bluePin, LOW);
      digitalWrite(greenPin, LOW);
      colorVariation(0, 0, 0);
    }
    
    // Set red light on
    void turnOnRed() {
      digitalWrite(redPin, HIGH);
    }
    
    // Set blue light on
    void turnOnBlue() {
      digitalWrite(bluePin, HIGH);
    }
    
    // Set green light on
    void turnOnGreen() {
      digitalWrite(greenPin, HIGH);
    }
    
    // Set yellow light on (red + green)
    void turnOnYellow() {
      digitalWrite(redPin, HIGH);
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
    
    // Blink yellow light - correctly implemented for yellow (red + green)
    void blinkYellow(int times, int duration) {
      for (int i = 0; i < times; i++) {
        // Turn on yellow (red + green)
        turnOnYellow();
        delay(duration);
        // Turn off all
        allOff();
        delay(duration);
      }
    }
    
    // Blink all colors sequentially
    void blinkAllColors(int times, int duration) {
      for (int i = 0; i < times; i++) {
        // Red
        turnOnRed();
        delay(duration);
        allOff();
        
        // Blue
        turnOnBlue();
        delay(duration);
        allOff();
        
        // Green
        turnOnGreen();
        delay(duration);
        allOff();
        
        // Yellow
        turnOnYellow();
        delay(duration);
        allOff();
        
        delay(duration);
      }
    }
    
    // Create a rainbow effect using analogWrite
    void rainbow(int cycles, int speed) {
      for (int j = 0; j < cycles; j++) {
        // One cycle of the rainbow
        for (int i = 0; i < 255; i += speed) {
          // Red to Yellow (increasing green)
          colorVariation(255, i, 0);
          delay(10);
        }
        
        for (int i = 0; i < 255; i += speed) {
          // Yellow to Green (decreasing red)
          colorVariation(255 - i, 255, 0);
          delay(10);
        }
        
        for (int i = 0; i < 255; i += speed) {
          // Green to Cyan (increasing blue)
          colorVariation(0, 255, i);
          delay(10);
        }
        
        for (int i = 0; i < 255; i += speed) {
          // Cyan to Blue (decreasing green)
          colorVariation(0, 255 - i, 255); 
          delay(10);
        }
        
        for (int i = 0; i < 255; i += speed) {
          // Blue to Magenta (increasing red)
          colorVariation(i, 0, 255); 
          delay(10);
        }
        
        for (int i = 0; i < 255; i += speed) {
          // Magenta to Red (decreasing blue)
          colorVariation(255, 0, 255 - i); 
          delay(10);
        }
      }     
      allOff();
    }

    void colorVariation(int red, int green, int blue) {
      analogWrite(redPin, red);
      analogWrite(greenPin, green);
      analogWrite(bluePin, blue);
    }
};

#endif 