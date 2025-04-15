class PedestrianLight {
  private:
    int redPin;
    int greenPin;
    
  public:
    // Constructor
    PedestrianLight(int red, int green) {
      redPin = red;
      greenPin = green;
      
      // Initialize pins
      pinMode(redPin, OUTPUT);
      pinMode(greenPin, OUTPUT);
    }
    
    // Set all lights off
    void allOff() {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
    }
    
    // Set red light on
    void turnOnRed() {
      digitalWrite(redPin, HIGH);
    }
    
    // Set green light on
    void turnOnGreen() {
      digitalWrite(greenPin, HIGH);
    }
    
    // Blink green light
    void blinkGreen(int times, int duration) {
      for (int i = 0; i < times; i++) {
        digitalWrite(greenPin, HIGH);
        delay(duration);
        digitalWrite(greenPin, LOW);
        delay(duration);
      }
    }
};