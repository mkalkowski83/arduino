#include <OneWire.h>
#include <DallasTemperature.h>

#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

//Tested on DS18B20 (digital sensor)

class TempSensor {
  private:
    OneWire oneWire;
    DallasTemperature sensors;
    
  public:    
    TempSensor(int pin) : oneWire(pin), sensors(&oneWire) {
    }
    
    void begin() {
      sensors.begin();
    }
    
    float readTemperature() {
      sensors.requestTemperatures();
      return sensors.getTempCByIndex(0);
    }

    int readTemperatureAsInt() {
      return (int)(readTemperature() * 100);
    }
};

#endif 