#ifndef SENSOR_READ_QUERY_H
#define SENSOR_READ_QUERY_H

#include "AM2302Sensor.h"
#include "SoilMoistureSensor.h"

class SensorReadQuery {
private:
    AM2302Sensor* sensor;
    SoilMoistureSensor* soilSensor;

public:
    SensorReadQuery(AM2302Sensor* sensor, SoilMoistureSensor* soilSensor) : 
        sensor(sensor),
        soilSensor(soilSensor) {
    }

    void begin() {
        sensor->begin();
        soilSensor->begin();
    }

    struct SensorData {
        float temperature;
        float humidity;
        int soilMoisturePercentage;
        int soilMoistureRawValue;
    };

    SensorData execute() {
        SensorData data;
        data.humidity = sensor->readHumidity();
        data.temperature = sensor->readTemperature();
        data.soilMoisturePercentage = soilSensor->readMoisturePercentage();
        data.soilMoistureRawValue = soilSensor->readRawValue();
        
        return data;
    }
};

#endif // SENSOR_READ_QUERY_H 