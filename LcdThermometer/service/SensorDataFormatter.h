#ifndef SENSOR_DATA_FORMATTER_H
#define SENSOR_DATA_FORMATTER_H

#include <stdio.h>
#include "../query/SensorReadQuery.h"

class SensorDataFormatter {
public:
    // ASCII code for degree symbol
    static const char DEGREE_SYMBOL = 223;
    
    // Format temperature and humidity values into a string
    static void format(char* buffer, float temperature, float humidity) {
        // Convert float to integers (multiply by 100 to preserve 2 decimal places)
        int tempInt = (int)(temperature * 100);
        int humInt = (int)(humidity * 100);
        // Display as integers with implicit decimal point
        sprintf(buffer, "Temp. %d.%02d%cC %d.%02d%%", tempInt / 100, tempInt % 100, DEGREE_SYMBOL, humInt / 100, humInt % 100);
    }
    
    // Format sensor data object into a string
    static void format(char* buffer, const SensorReadQuery::SensorData& data) {
        // Convert float to integers (multiply by 100 to preserve 2 decimal places)
        int tempInt = (int)(data.temperature * 100);
        int humInt = (int)(data.humidity * 100);
        sprintf(buffer, "Temp. %d.%02d%cC Hum. %d.%02d%% Soil:%d%%", tempInt / 100, tempInt % 100, DEGREE_SYMBOL, humInt / 100, humInt % 100, data.soilMoisturePercentage);
    }
};

#endif