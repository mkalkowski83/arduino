#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H

#include <Arduino.h>

class SerialPortManager {
private:
    unsigned long baudRate;
    bool initialized;

public:
    SerialPortManager(unsigned long baud = 9600) 
        : baudRate(baud), initialized(false) {
    }
    
    void begin() {
        if (!initialized) {
            Serial.begin(baudRate);
            initialized = true;
        }
    }
    
    void print(const char* message) {
        if (initialized) {
            Serial.print(message);
        }
    } 
    
    void print(int value) {
        if (initialized) {
            Serial.print(value);
        }
    }

    void print(float value, int precision = 2) {
        if (initialized) {
            Serial.print(value, precision);
        }
    }

    // Helper method for printing
    void println(const char* message) {
        if (initialized) {
            Serial.println(message);
        }
    }
    
    // Helper method for printing values
    void println(int value) {
        if (initialized) {
            Serial.println(value);
        }
    }
    
    // Helper method for printing values with float precision
    void println(float value, int precision = 2) {
        if (initialized) {
            Serial.println(value, precision);
        }
    }
};

#endif 