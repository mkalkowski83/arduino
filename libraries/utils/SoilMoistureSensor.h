#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

class SoilMoistureSensor {
  private:
    int sensorPin;
    int airValue;    // Value in air (dry)
    int waterValue;  // Value in water (wet)
    
  public:    
    SoilMoistureSensor(int pin, int air = 1022, int water = 409) 
      : sensorPin(pin), airValue(air), waterValue(water) {
    }
    
    void begin() {
      pinMode(sensorPin, INPUT);
    }
    
    int readRawValue() {
      return analogRead(sensorPin);
    }
    
    // Returns moisture percentage (0-100)
    // 0% = completely dry (air value)
    // 100% = completely wet (water value)
    int readMoisturePercentage() {
      int rawValue = readRawValue();
      return map(rawValue, airValue, waterValue, 0, 100);
    }
    
    // Calibrate sensor with new values
    void calibrate(int air, int water) {
      airValue = air;
      waterValue = water;
    }
};

#endif // SOIL_MOISTURE_SENSOR_H 