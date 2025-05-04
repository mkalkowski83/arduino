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


public:
    EnvironmentSensorLcdController(LcdManager* lcdManager, SensorReadQuery* query, SerialPortManager* serialManager): 
    lcdManager(lcdManager), query(query), serialManager(serialManager), timedExecutor(UPDATE_INTERVAL), scrollExecutor(SCROLL_INTERVAL) {
    }
    
    void begin() override {
        lcdManager->begin();
        query->begin();
        serialManager->begin();
        
        // Initial setup of display with scrolling text in second row
        lcdManager->clear();        
    }

    void update() override {
        // Update sensor data at a slower interval
        if (timedExecutor.shouldExecute()) {
            // Get sensor data
            SensorReadQuery::SensorData data = query->execute();
            
            // Format temperature and humidity for display in first row
            char buffer[70];
            SensorDataFormatter::format(buffer, data);
            
            // Append soil moisture to the display output
            lcdManager->setScrollingText(buffer, 0);
            
            // Send soil moisture data to serial port
            serialManager->println("Soil Moisture Data: ");
            serialManager->print(data.soilMoisturePercentage, 2);
            serialManager->println("");
            serialManager->println("Raw Value: ");
            serialManager->print(data.soilMoistureRawValue);
            serialManager->println("");
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