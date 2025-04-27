#ifndef TEMPERATURE_HUMIDITY_FORMATTER_H
#define TEMPERATURE_HUMIDITY_FORMATTER_H

#include <stdio.h>

class TemperatureHumidityFormatter {
public:
    // ASCII code for degree symbol
    static const char DEGREE_SYMBOL = 223;
    
    // Format temperature and humidity values into a string
    static void format(char* buffer, float temperature, float humidity) {
        // Convert float to integers (multiply by 100 to preserve 2 decimal places)
        int tempInt = (int)(temperature * 100);
        int humInt = (int)(humidity * 100);
        // Display as integers with implicit decimal point
        sprintf(buffer, "%d.%02d%cC %d.%02d%%", tempInt / 100, tempInt % 100, DEGREE_SYMBOL, humInt / 100, humInt % 100);
    }
};

#endif // TEMPERATURE_HUMIDITY_FORMATTER_H 