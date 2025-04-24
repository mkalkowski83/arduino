#ifndef TEMPERATURE_CONTROLLER_H
#define TEMPERATURE_CONTROLLER_H

#include <TemperatureSensor.h>
#include <LcdManager.h>
#include <Controller.h>

class TemperatureController : public Controller {
private:
  TemperatureSensor &temperatureSensor;
  LcdManager &lcdManager;
  
public:
  TemperatureController(TemperatureSensor &tempSensor, LcdManager &lcd)
    : temperatureSensor(tempSensor), lcdManager(lcd) {}
  
  virtual ~TemperatureController() {}
  
  void begin() override {
    temperatureSensor.begin();
    lcdManager.begin();
  }
  
  void update() override {
    float currentTemperature = temperatureSensor.readTemperature();
    displayTemperature(currentTemperature);
  }
  
  const char* getName() override {
    return "TemperatureController";
  }
  
private:
  void displayTemperature(float temperature, String unit) {
    // Clear row 0 first
    lcdManager.clearRow(0);
    
    // Display temperature on the first row
    lcdManager.setCursor(0, 0);
    
    // Format temperature string with at most 5 characters (XX.XX)
    char tempStr[6];
    dtostrf(temperature, 5, 2, tempStr);
    
    // Use safe print for unit to possibly wrap if needed
    lcdManager.print(tempStr);
    lcdManager.safePrint(unit);
  }
};

#endif // TEMPERATURE_CONTROLLER_H 