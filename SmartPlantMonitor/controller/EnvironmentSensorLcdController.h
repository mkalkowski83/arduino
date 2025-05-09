#ifndef ENVIRONMENT_SENSOR_LCD_CONTROLLER_H
#define ENVIRONMENT_SENSOR_LCD_CONTROLLER_H

#include "Controller.h"
#include "LcdManager.h"
#include "TimedExecutor.h"
#include "../query/SensorReadQuery.h"
#include "../service/SensorDataFormatter.h"
#include "SerialPortManager.h"

class EnvironmentSensorLcdController : public Controller {
private:
    static const unsigned long UPDATE_INTERVAL = 2000; // ms
    static const unsigned long SCROLL_INTERVAL = 300; // ms
    
    LcdManager* lcdManager;
    SensorReadQuery* query;
    SerialPortManager* serialManager;
    TimedExecutor timedExecutor;
    TimedExecutor scrollExecutor;
    
    bool scrollingInitialized = false;

public:
    EnvironmentSensorLcdController(LcdManager* lcdManager, SensorReadQuery* query, SerialPortManager* serialManager): 
    lcdManager(lcdManager), 
    query(query), 
    serialManager(serialManager), 
    timedExecutor(UPDATE_INTERVAL), 
    scrollExecutor(SCROLL_INTERVAL) {
    }
    
    ~EnvironmentSensorLcdController() {
        if (lcdManager != nullptr) {
            lcdManager->clear();
        }
    }
    
    void begin() override {
        lcdManager->begin();
        query->begin();
        serialManager->begin();
        
        // Initial setup of display
        lcdManager->clear();
        
        scrollingInitialized = false;
    }

    void update() override {
        // Update sensor data at a slower interval
        if (timedExecutor.shouldExecute()) {
            // Get sensor data
            SensorReadQuery::SensorData data = query->execute();
            
            // Format data for display
            char buffer[100];
            SensorDataFormatter::format(buffer, data);
            
            // Update scrolling text without resetting position
            if (scrollingInitialized) {
                lcdManager->updateScrollingTextContent(buffer, 0);
            } else {
                // Initial setup if not done in begin() for some reason
                lcdManager->setScrollingText(buffer, 0);
                scrollingInitialized = true;
            }
        }

        // Update scrolling animation at a faster interval
        if (scrollExecutor.shouldExecute()) {
            lcdManager->updateScrolling();
        }
    }

    const char* getName() override {
        return "EnvironmentSensorLcdController";
    }
};

#endif // ENVIRONMENT_SENSOR_LCD_CONTROLLER_H 