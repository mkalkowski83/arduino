#ifndef TEMPERATURE_DISPLAY_H
#define TEMPERATURE_DISPLAY_H

#include "TempSensor.h"
#include "DisplayManager.h"

class TemperatureDisplay {
private:
    TempSensor& sensor;
    DisplayManager& display;
    unsigned long lastUpdate = 0;
    int currentValue = 0;
    const unsigned long UPDATE_INTERVAL = 1000; // 1 second

public:
    TemperatureDisplay(TempSensor& tempSensor, DisplayManager& displayManager)
        : sensor(tempSensor), display(displayManager) {
    }

    void begin() {
        sensor.begin();
        display.setup();
    }

    void update() {
        if (millis() - lastUpdate >= UPDATE_INTERVAL) {
            currentValue = sensor.readTemperatureAsInt();
            lastUpdate = millis();
        }
        display.showNumber(currentValue, 2);
    }
};

#endif 