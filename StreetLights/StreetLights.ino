#include "PedestrianLight.h"
#include "TrafficLight.h"
#include "Button.h"

// Create traffic light and pedestrian light objects and pin initilization
TrafficLight carLight(8, 10, 12);  // red, yellow, green
PedestrianLight peopleLight(5, 7); // red, green
Button button(2);

void setup() {
  
}

void loop() {
  // Normal state: Car green, pedestrian red
  if (button.isPushed()) {
    //after 5s swtich car light to yelow
    delay(5000);
    carLight.allOff();
    carLight.turnOnYellow();
    // after 5s switch to red light
    delay(5000);
    carLight.allOff();
    carLight.turnOnRed();
    
    peopleLight.allOff();
    peopleLight.turnOnGreen();
    delay(5000);
    //make grean light for people blinking
    peopleLight.blinkGreen(5, 500);

    // turn on red and yelow for car 
    carLight.allOff();
    carLight.turnOnRed();
    carLight.turnOnYellow();
    
    peopleLight.allOff();
    carLight.allOff();    
  }
  
  carLight.turnOnGreen();
  peopleLight.turnOnRed();
    
}
