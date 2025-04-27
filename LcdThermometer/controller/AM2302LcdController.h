#ifndef AM2302_LCD_CONTROLLER_H
#define AM2302_LCD_CONTROLLER_H

#include "Controller.h"
#include "LcdManager.h"
#include "TimedExecutor.h"
#include "../query/AM2302Query.h"
#include "../service/TemperatureHumidityFormatter.h"

class AM2302LcdController : public Controller {
private:
    static const unsigned long UPDATE_INTERVAL = 2000; // ms
    static const unsigned long SCROLL_INTERVAL = 300; // ms
    
    LcdManager* lcdManager;
    AM2302Query* query;
    TimedExecutor timedExecutor;
    TimedExecutor scrollExecutor;

public:
    AM2302LcdController(LcdManager* lcdManager, AM2302Query* query): 
    lcdManager(lcdManager), query(query), timedExecutor(UPDATE_INTERVAL), scrollExecutor(SCROLL_INTERVAL) {
    }
    
    void begin() override {
        lcdManager->begin();
        query->begin();
        
        // Initial setup of display with scrolling text in second row
        lcdManager->clear();
        lcdManager->setScrollingText("Temperature and Humidity Monitor - Created by M.K. - Arduino", 1);
    }

    void update() override {
        // Update sensor data at a slower interval
        if (timedExecutor.shouldExecute()) {
            // Get sensor data
            AM2302Query::SensorData data = query->execute();
            
            // Format temperature and humidity for display in first row
            char buffer[50];
            TemperatureHumidityFormatter::format(buffer, data.temperature, data.humidity);
            
            // Update first row with temperature and humidity
            lcdManager->printAtRow(buffer, 0);
        }
        
        // Update scrolling animation at a faster interval
        if (scrollExecutor.shouldExecute()) {
            lcdManager->updateScrolling();
        }
    }

    const char* getName() override {
        return "AM2302LcdController";
    }
};

#endif // AM2302_LCD_CONTROLLER_H 