#ifndef TEMPERATURE_DISPLAY_CONTROLLER_H
#define TEMPERATURE_DISPLAY_CONTROLLER_H

#include "TemperatureSensor.h"
#include "DisplayManager.h"
#include "Controller.h"
#include "TimedExecutor.h"

class TemperatureDisplayController : public Controller {
private:
    TemperatureSensor& sensor;
    DisplayManager& display;
    int currentValue = 0;
    
    // Time executors for different operations
    TimedExecutor temperatureExecutor;
    TimedExecutor displaySetExecutor;
    TimedExecutor displayRefreshExecutor;

    // Private method to update temperature
    void updateTemperature() {
        currentValue = sensor.readTemperatureAsInt();
    }

    // Private method to set number on display
    void updateDisplay() {
        display.showNumber(currentValue, 2);
    }

    // Private method to refresh display for multiplexing
    void refreshDisplay() {
        display.refreshCurrentDisplay();
    }

public:
    TemperatureDisplayController(TemperatureSensor& tempSensor, DisplayManager& displayManager)
        : sensor(tempSensor), 
          display(displayManager),
          // Initialize executors with their respective intervals
          temperatureExecutor(5000),      // Temperature reading every 5 seconds
          displaySetExecutor(1000),       // Display update every 1 second
          displayRefreshExecutor(5) {     // Display refresh every 5ms for smooth multiplexing
    }

    // Implementation of begin method from Controller interface
    void begin() override {
        sensor.begin();
        display.setup();
        
        // Take initial temperature reading
        updateTemperature();
        
        // Set initial value on display
        updateDisplay();
    }

    // Implementation of update method from Controller interface
    void update() override {
        // Check if it's time to update temperature
        if (temperatureExecutor.shouldExecute()) {
            updateTemperature();
            return;
        }
        
        // Check if it's time to update display
        if (displaySetExecutor.shouldExecute()) {
            updateDisplay();
            return;
        } 
        // Only check for refresh if we didn't just update the display
        if (displayRefreshExecutor.shouldExecute()) {
            refreshDisplay();
            return;
        }
    }
    
    // Implementation of getName method from Controller interface
    const char* getName() override {
        return "TemperatureDisplayController";
    }
};

#endif 