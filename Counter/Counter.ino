#include "SevSeg.h"
SevSeg sevseg; 

void setup(){
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};

  bool resistorsOnSegments = true; 
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(20);
  
  randomSeed(analogRead(0)); // Initialize random number generator with noise from unconnected analog pin
}

void loop(){
    static int counter = 0; // Static variable to maintain count between loop iterations
    static unsigned long lastUpdate = 0; // To track when to increment counter
    
    unsigned long currentMillis = millis();
    
    // Update counter once per second without blocking display refresh
    if (currentMillis - lastUpdate >= 1000) {
        counter++; // Increment counter
        if(counter > 9999) { // Reset when greater than 9999
            counter = 0;
        }
        lastUpdate = currentMillis;
    }
    
    sevseg.setNumber(counter, 0);
    sevseg.refreshDisplay(); // This needs to be called continuously for all digits to display properly
}