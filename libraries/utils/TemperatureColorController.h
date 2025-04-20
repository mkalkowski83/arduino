#ifndef TEMPERATURE_COLOR_CONTROLLER_H
#define TEMPERATURE_COLOR_CONTROLLER_H

#include "TemperatureSensor.h"
#include "RgbLed.h"
#include "Controller.h"
#include "TimedExecutor.h"

class TemperatureColorController : public Controller {
private:
  TemperatureSensor& tempSensor;
  RgbLed& rgbLed;
  float tempLow;
  float tempMedium;
  float tempHigh;
  float tempVeryHigh;
  float currentTemp;
  
  // Timer executor for temperature reading
  TimedExecutor temperatureExecutor;
  
  // Set LED color based on temperature
  void setColorBasedOnTemperature() {
    // Always start with all LEDs off
    rgbLed.allOff();

    // Below low threshold - blue (cold)
    if (currentTemp < tempLow) {
      rgbLed.turnOnBlue();
      return;
    }
    
    // Between low and medium threshold - yellow (borderline)
    if (currentTemp >= tempLow && currentTemp < tempMedium) {
      rgbLed.turnOnGreen();
      return;
    }
    
    // Between medium and high threshold - blue (high)
    if (currentTemp >= tempMedium && currentTemp < tempHigh) {
      rgbLed.turnOnYellow();
      return;
    }
    
    // Between high and very high threshold - blinking yellow (warning)
    if (currentTemp >= tempHigh && currentTemp < tempVeryHigh) {
      rgbLed.turnOnPurple();
      return;
    }
    
    // Above very high threshold - red (critical)
    if (currentTemp >= tempVeryHigh) {
      rgbLed.turnOnRed();
      return;
    }
  }
  
  // Update the current temperature reading
  void readTemperature() {
    currentTemp = tempSensor.readTemperature();
  }

public:
  TemperatureColorController(TemperatureSensor& sensor, RgbLed& led, 
                             float lowThreshold = 22.0, 
                             float mediumThreshold = 23.0, 
                             float highThreshold = 24.0,
                             float veryHighThreshold = 25.0,
                             unsigned long updateInterval = 5000) 
    : tempSensor(sensor), 
      rgbLed(led),
      tempLow(lowThreshold),
      tempMedium(mediumThreshold),
      tempHigh(highThreshold),
      tempVeryHigh(veryHighThreshold),
      currentTemp(0.0),
      temperatureExecutor(updateInterval) {
  }

  // Implementation of begin method from Controller interface
  void begin() override {
    // Initialize if needed
    rgbLed.allOff();
    readTemperature();
    setColorBasedOnTemperature();
  }

  // Implementation of update method from Controller interface
  void update() override {
    // Check if it's time to update temperature and LED color
    if (temperatureExecutor.shouldExecute()) {
      // Get current temperature
      readTemperature();
      
      // Set appropriate LED color based on temperature
      setColorBasedOnTemperature();
    }
  }

  // Implementation of getName method from Controller interface
  const char* getName() override {
    return "TemperatureColorController";
  }

  // Setters for thresholds if needed
  void setLowThreshold(float threshold) {
    tempLow = threshold;
  }

  void setMediumThreshold(float threshold) {
    tempMedium = threshold;
  }

  void setHighThreshold(float threshold) {
    tempHigh = threshold;
  }
  
  void setVeryHighThreshold(float threshold) {
    tempVeryHigh = threshold;
  }
  
  // Set new update interval
  void setUpdateInterval(unsigned long newInterval) {
    temperatureExecutor.setInterval(newInterval);
  }
};

#endif 