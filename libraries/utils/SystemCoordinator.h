#ifndef SYSTEM_COORDINATOR_H
#define SYSTEM_COORDINATOR_H

#include "Controller.h"
#include <Arduino.h>

// Maximum number of controllers that can be registered
#define MAX_CONTROLLERS 10

// Class that coordinates the entire system operation
class SystemCoordinator {
private:
    // Array of controllers
    Controller* controllers[MAX_CONTROLLERS];
    
    // Number of registered controllers
    uint8_t controllerCount = 0;

public:
    SystemCoordinator() {}
    
    // Adds a controller to the system
    bool addController(Controller* controller) {
        if (controllerCount >= MAX_CONTROLLERS) {
            return false; // Cannot add more controllers
        }
        
        controllers[controllerCount] = controller;
        controllerCount++;
        
        return true;
    }
    
    // Alias for addController for backward compatibility
    bool addControllerAlways(Controller* controller) {
        return addController(controller);
    }
    
    // Initialize all controllers
    void begin() {
        for (uint8_t i = 0; i < controllerCount; i++) {
            controllers[i]->begin();
        }
    }
    
    // Update all controllers
    void update() {
        for (uint8_t i = 0; i < controllerCount; i++) {
            controllers[i]->update();
        }
    }
};

#endif 