#ifndef TEMPERATURE_BUZZER_CONTROLLER_H
#define TEMPERATURE_BUZZER_CONTROLLER_H

#include "TemperatureSensor.h"
#include "Buzzer.h"
#include "Controller.h"
#include "TimedExecutor.h"

class TemperatureBuzzerController : public Controller {
private:
  TemperatureSensor& tempSensor;
  Buzzer& buzzer;
  float tempThreshold;
  float currentTemp;
  
  // Timer executor for temperature reading and buzzer control
  TimedExecutor temperatureExecutor;
  TimedExecutor buzzerExecutor;
  
  // Beep pattern variables
  bool beepActive;
  unsigned long beepDuration;
  unsigned long pauseDuration;
  
  // Check temperature and control the buzzer
  void checkTemperatureAndBeep() {
    currentTemp = tempSensor.readTemperature();
    
    // If temperature is above threshold, start beeping pattern
    if (currentTemp >= tempThreshold) {
      beepActive = true;
      return;
    }

    beepActive = false;
    buzzer.turnOff();
    return;
  }
  
  // Handle beep pattern
  void manageBuzzerState() {
    if (!beepActive) {
      return;
    }
    
    // Toggle buzzer state for the beep pattern
    if (buzzer.isOn()) {
      buzzer.turnOff();
      buzzerExecutor.setInterval(pauseDuration);
      return;
    }

    buzzer.turnOn();
    buzzerExecutor.setInterval(beepDuration);    
  }

public:
  TemperatureBuzzerController(
    TemperatureSensor& sensor, 
    Buzzer& buzzerDevice,
    float highTempThreshold = 38.0,
    unsigned long tempCheckInterval = 5000,
    unsigned long beepLength = 200,
    unsigned long beepPause = 800)
    : tempSensor(sensor), 
      buzzer(buzzerDevice),
      tempThreshold(highTempThreshold),
      currentTemp(0.0),
      temperatureExecutor(tempCheckInterval),
      buzzerExecutor(beepLength),
      beepActive(false),
      beepDuration(beepLength),
      pauseDuration(beepPause) {
  }

  // Implementation of begin method from Controller interface
  void begin() override {
    buzzer.turnOff();
    currentTemp = tempSensor.readTemperature();
    beepActive = (currentTemp >= tempThreshold);
  }

  // Implementation of update method from Controller interface
  void update() override {
    // Check if it's time to update temperature
    if (temperatureExecutor.shouldExecute()) {
      checkTemperatureAndBeep();
      return;
    }
    
    // Manage buzzer beep pattern if active
    if (beepActive && buzzerExecutor.shouldExecute()) {
      manageBuzzerState();
      return;
    }
  }

  // Implementation of getName method from Controller interface
  const char* getName() override {
    return "TemperatureBuzzerController";
  }

  // Setters for parameters
  void setTemperatureThreshold(float threshold) {
    tempThreshold = threshold;
  }
  
  void setBeepDuration(unsigned long duration) {
    beepDuration = duration;
  }
  
  void setPauseDuration(unsigned long duration) {
    pauseDuration = duration;
  }
  
  void setTempCheckInterval(unsigned long interval) {
    temperatureExecutor.setInterval(interval);
  }
};

#endif 