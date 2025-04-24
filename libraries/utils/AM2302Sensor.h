#ifndef AM2302SENSOR_H
#define AM2302SENSOR_H

#include "Grove_Temperature_And_Humidity_Sensor.h"

class AM2302Sensor {
private:
    DHT* dht;

public:
    AM2302Sensor(int pin) { 
        dht = new DHT(pin, DHT22);
    }

    void begin() {
        dht->begin();
    }

    ~AM2302Sensor() {
        if (dht) {
            delete dht;
            dht = nullptr;
        }
    }

    float readTemperature() {
        return dht->readTemperature();
    }

    float readHumidity() {
        return dht->readHumidity();
    }
};

#endif // AM2302SENSOR_H 