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
    
    LcdManager* lcdManager;
    AM2302Query* query;
    TimedExecutor timedExecutor;

public:
    AM2302LcdController(LcdManager* lcdManager, AM2302Query* query): 
    lcdManager(lcdManager), query(query), timedExecutor(UPDATE_INTERVAL) {
    }
    
    void begin() override {
        lcdManager->begin();
        query->begin();
    }

    void update() override {
        lcdManager->updateScrollText();
        
        if (timedExecutor.shouldExecute()) {
            AM2302Query::SensorData data = query->execute();
            
            char buffer[50];
            
            TemperatureHumidityFormatter::format(buffer, data.temperature, data.humidity);
            
            lcdManager->clearRow(0);
            lcdManager->printAt(0, 0, buffer);
            
            lcdManager->setScrollText("Temperature and Humidity Monitor - Created by M.K. - Arduino", 1);
        }
    }

    const char* getName() override {
        return "AM2302LcdController";
    }
};

#endif // AM2302_LCD_CONTROLLER_H 