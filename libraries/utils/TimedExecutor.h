#ifndef TIMED_EXECUTOR_H
#define TIMED_EXECUTOR_H

#include <Arduino.h>

// Class managing operations performed at specified time intervals
class TimedExecutor {
private:
    unsigned long lastExecutionTime = 0;
    unsigned long interval;

public:
    TimedExecutor(unsigned long executionInterval) 
        : interval(executionInterval) {
    }

    // Changes the execution interval
    void setInterval(unsigned long newInterval) {
        interval = newInterval;
    }

    // Checks if an operation should be executed and updates the time
    bool shouldExecute() {
        unsigned long currentMillis = millis();
        if (currentMillis - lastExecutionTime >= interval) {
            lastExecutionTime = currentMillis;
            return true;
        }
        return false;
    }

    // Resets the time counter, can also be used to force immediate execution on next check
    void reset() {
        lastExecutionTime = millis();
    }
};

#endif 