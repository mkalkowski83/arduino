#ifndef PUMP_MANAGER_H
#define PUMP_MANAGER_H

#include <Arduino.h>

class PumpManager {
private:
    uint8_t pumpPin; // Pin controlling the pump
    bool isRunning;  // Current state of the pump

public:
    PumpManager(uint8_t pin) : pumpPin(pin), isRunning(false) {
        // Initialize the pin as output
        pinMode(pumpPin, OUTPUT);
        // Ensure pump is off at initialization
        digitalWrite(pumpPin, LOW);
    }
    // Turn on the pump
    void turnOn() {
        digitalWrite(pumpPin, HIGH);
        isRunning = true;
    }
    
    // Turn off the pump
    void turnOff() {
        digitalWrite(pumpPin, LOW);
        isRunning = false;
    }
    
    // Get current state of the pump
    bool isPumpRunning() const {
        return isRunning;
    }
};

#endif // PUMP_MANAGER_H 