#ifndef AM2302_LCD_CONTROLLER_H
#define AM2302_LCD_CONTROLLER_H

#include "Controller.h"
#include "LcdManager.h"
#include "AM2302Sensor.h"
#include "TimedExecutor.h"
#include "SerialPortManager.h"

class AM2302LcdController : public Controller {
private:
    LcdManager* lcdManager;
    AM2302Sensor* sensor;
    TimedExecutor timedExecutor;
    SerialPortManager& serialManager;

public:
    AM2302LcdController(LcdManager* lcdManager, AM2302Sensor* sensor, SerialPortManager& serialManager, unsigned long updateInterval = 2000): 
    lcdManager(lcdManager), sensor(sensor), serialManager(serialManager), timedExecutor(updateInterval) {
    }

    
    void begin() override {
        serialManager.begin();
        serialManager.println("AM2302LcdController initialized");
        lcdManager->begin();
        sensor->begin();
    }

    void update() override {
        // Check if it's time to update the display
        if (timedExecutor.shouldExecute()) {
            serialManager.println("Attempting to read sensor data...");
            
            // Read temperature and humidity separately instead of using readTempAndHumidity
            float humidity = sensor->readHumidity();
            float temperature = sensor->readTemperature();
            
            char buffer[50];
            
            // Create combined messages
            sprintf(buffer, "Humidity: %.2f %%", humidity);
            serialManager.println(buffer);
            
            sprintf(buffer, "Temperature: %.2f C", temperature);
            serialManager.println(buffer);
            
            // Clear the LCD screen
            lcdManager->clearScreen();
            
            // Display temperature on the first row
            lcdManager->printAt(0, 0, "Temp: ");
            lcdManager->print(temperature);
            lcdManager->print(" C");
            
            // Display humidity on the second row
            lcdManager->printAt(0, 1, "Humidity: ");
            lcdManager->print(humidity);
            lcdManager->print("%");
        }
    }

    const char* getName() override {
        return "AM2302LcdController";
    }
};

#endif // AM2302_LCD_CONTROLLER_H 