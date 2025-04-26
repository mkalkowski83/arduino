#ifndef AM2302_QUERY_H
#define AM2302_QUERY_H

#include "AM2302Sensor.h"

class AM2302Query {
private:
    AM2302Sensor* sensor;

public:
    AM2302Query(AM2302Sensor* sensor) : 
        sensor(sensor) {
    }

    void begin() {
        sensor->begin();
    }

    struct SensorData {
        float temperature;
        float humidity;
    };

    SensorData execute() {
        SensorData data;
        data.humidity = sensor->readHumidity();
        data.temperature = sensor->readTemperature();
        
        return data;
    }
};

#endif // AM2302_QUERY_H 