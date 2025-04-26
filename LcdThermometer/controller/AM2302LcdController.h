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
        // Check if it's time to update the display
        if (timedExecutor.shouldExecute()) {
            // Use the query to read sensor data
            AM2302Query::SensorData data = query->execute();
            
            char buffer[50];
            
            // Format temperature and humidity values
            TemperatureHumidityFormatter::format(buffer, data.temperature, data.humidity);
            
            lcdManager->clearScreen();
            lcdManager->printAt(0, 0, buffer);
            lcdManager->printAt(0, 1, "Kochana Polcia i TObi:)");
        }
    }

    const char* getName() override {
        return "AM2302LcdController";
    }
};

#endif // AM2302_LCD_CONTROLLER_H 