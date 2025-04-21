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
    TemperatureDisplayController(
        TemperatureSensor& tempSensor, 
        DisplayManager& displayManager,
        unsigned long temperatureReadInterval = 5000,   // Default: 5 seconds
        unsigned long displayUpdateInterval = 5000,     // Default: 5 seconds
        unsigned long displayRefreshInterval = 1        // Default: 1ms - faster refresh
    )
        : sensor(tempSensor), 
          display(displayManager),
          // Initialize executors with their respective intervals
          temperatureExecutor(temperatureReadInterval),
          displaySetExecutor(displayUpdateInterval),
          displayRefreshExecutor(displayRefreshInterval) {
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
        // Check if it's time to refresh the display first - most important operation
        if (displayRefreshExecutor.shouldExecute()) {
            refreshDisplay();
        }
        
        // Check if it's time to update temperature
        if (temperatureExecutor.shouldExecute()) {
            updateTemperature();
            updateDisplay(); // Always update display after temperature reading
        }
        
        // Check if it's time to update display without a temperature change
        else if (displaySetExecutor.shouldExecute()) {
            updateDisplay();
        }
    }
    
    // Implementation of getName method from Controller interface
    const char* getName() override {
        return "TemperatureDisplayController";
    }
};

#endif 