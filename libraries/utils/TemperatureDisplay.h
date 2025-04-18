#ifndef TEMPERATURE_DISPLAY_CONTROLLER_H
#define TEMPERATURE_DISPLAY_CONTROLLER_H

#include "TempSensor.h"
#include "DisplayManager.h"
#include "Controller.h"

class TemperatureDisplayController : public Controller {
private:
    TempSensor& sensor;
    DisplayManager& display;
    unsigned long lastUpdate = 0;
    unsigned long lastSetNumber = 0;
    int currentValue = 0;
    const unsigned long UPDATE_INTERVAL = 5000;       // Odczyt temperatury co 5 sekund
    const unsigned long SET_NUMBER_INTERVAL = 1000;   // Ustawianie numeru co 1 sekundę
    const unsigned long REFRESH_INTERVAL = 5;         // Odświeżanie wyświetlacza co 5ms
    unsigned long lastRefresh = 0;

public:
    TemperatureDisplayController(TempSensor& tempSensor, DisplayManager& displayManager)
        : sensor(tempSensor), display(displayManager) {
    }

    // Implementacja metody begin z interfejsu Controller
    void begin() override {
        sensor.begin();
        display.setup();
        // Wykonaj pierwszy odczyt temperatury
        currentValue = sensor.readTemperatureAsInt();
        // Ustaw początkową wartość na wyświetlaczu
        display.showNumber(currentValue, 2);
    }

    // Implementacja metody update z interfejsu Controller
    void update() override {
        unsigned long currentMillis = millis();
        
        // 1. Aktualizuj wartość temperatury co 5 sekund
        if (currentMillis - lastUpdate >= UPDATE_INTERVAL) {
            currentValue = sensor.readTemperatureAsInt();
            lastUpdate = currentMillis;
        }
        
        // 2. Ustaw numer na wyświetlaczu co 1 sekundę
        if (currentMillis - lastSetNumber >= SET_NUMBER_INTERVAL) {
            display.showNumber(currentValue, 2);
            lastSetNumber = currentMillis;
        } 
        // 3. Odświeżaj wyświetlacz często, aby zapewnić płynne multipleksowanie
        else if (currentMillis - lastRefresh >= REFRESH_INTERVAL) {
            display.refreshCurrentDisplay();
            lastRefresh = currentMillis;
        }
    }
    
    // Implementacja metody getName z interfejsu Controller
    const char* getName() override {
        return "TemperatureDisplayController";
    }
};

#endif 