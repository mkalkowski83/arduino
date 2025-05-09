#ifndef IRRIGATION_SERVICE_H
#define IRRIGATION_SERVICE_H

#include <Arduino.h>
#include "../query/SensorReadQuery.h"
#include "../utils/PumpManager.h"

class IrrigationService {
private:
    PumpManager* pumpManager;
    SensorReadQuery* sensorQuery;
    
    unsigned long wateringDuration;   // Duration in milliseconds
    int moistureThreshold;            // Min soil moisture threshold (%) - START watering
    int maxMoistureThreshold;         // Max soil moisture threshold (%) - STOP watering
    bool autoWateringEnabled;         // Automatic watering flag
    
    unsigned long startTime;          // Start time of current watering
    unsigned long lastWateringTime;   // When the last watering cycle ended
    static const unsigned long REST_PERIOD = 60000; // 1 minute in milliseconds
    
    // Helper method to check if watering is active
    bool isWatering() const {
        return pumpManager != nullptr && pumpManager->isPumpRunning();
    }
    
    // Check if enough time has passed since last watering
    bool canStartNewWateringCycle() const {
        unsigned long timeSinceLastWatering = millis() - lastWateringTime;
        Serial.print(F("Time since last watering (ms): "));
        Serial.println(timeSinceLastWatering);
        Serial.print(F("REST_PERIOD (ms): "));
        Serial.println(REST_PERIOD);
        return timeSinceLastWatering >= REST_PERIOD;
    }

public:
    IrrigationService(
        PumpManager* pump, 
        SensorReadQuery* sensor,
        unsigned long duration = 5000, 
        int minThreshold = 30,
        int maxThreshold = 70,
        bool autoWatering = false
        ) : pumpManager(pump),
          sensorQuery(sensor),
          wateringDuration(duration),
          moistureThreshold(minThreshold),
          maxMoistureThreshold(maxThreshold),
          autoWateringEnabled(autoWatering),
          startTime(0),
          lastWateringTime(0) {
        // Initialize with a time in the past to allow immediate first watering if needed
        lastWateringTime = millis() - REST_PERIOD - 1000;
    }
    
    ~IrrigationService() {
        // Make sure pump is off when service is destroyed
        if (pumpManager != nullptr) {
            pumpManager->turnOff();
        }
    }
    
    void begin() {
        if (sensorQuery != nullptr) {
            sensorQuery->begin();
        }
        
        if (pumpManager != nullptr) {
            stopWatering(); // Ensure pump is off initially
        }
    }
    
    // Check and update irrigation status
    void update() {
        // Only proceed if sensor is available
        if (sensorQuery == nullptr) return;
        
        // Get current soil moisture data
        SensorReadQuery::SensorData data = sensorQuery->execute();
        
        Serial.print(F("Raw data: "));
        Serial.println(data.soilMoistureRawValue);
        Serial.print(F("Percentage: "));
        Serial.println(data.soilMoisturePercentage);
        
        // Check if we need to stop current watering
        if (isWatering()) {
            // Stop watering if max time has elapsed or moisture threshold reached
            if (millis() - startTime >= wateringDuration || 
                data.soilMoisturePercentage >= maxMoistureThreshold) {
                Serial.println(F("Stopping watering because of max time or moisture threshold reached"));
                stopWatering();
            }
            return; // Don't check for starting while already watering
        }
        
        // Check if we're still in the rest period after last watering
        bool canStart = canStartNewWateringCycle();
        if (!canStart) {
            long msLeft = (REST_PERIOD - (millis() - lastWateringTime));
            if (msLeft > 0) {
                unsigned long secondsLeft = msLeft / 1000;
                Serial.print(F("Resting after watering. Seconds left: "));
                Serial.println(secondsLeft);
            } else {
                Serial.println(F("Rest period finished but canStartNewWateringCycle returned false!"));
            }
            return;
        }
        
        // Check if auto watering is enabled and soil is dry
        Serial.print(F("Auto watering enabled: "));
        Serial.println(autoWateringEnabled ? F("YES") : F("NO"));
        Serial.print(F("Moisture threshold: "));
        Serial.println(moistureThreshold);
        
        if (autoWateringEnabled && data.soilMoisturePercentage < moistureThreshold) {
            Serial.print(F("Starting watering. Moisture: "));
            Serial.print(data.soilMoisturePercentage);
            Serial.println(F("% is below threshold"));
            startWatering();
        } else if (autoWateringEnabled) {
            Serial.println(F("Moisture level OK, no watering needed"));
        }
    }
    
    // Start watering
    void startWatering() {
        if (!isWatering() && pumpManager != nullptr) {
            pumpManager->turnOn();
            startTime = millis();
            Serial.println(F("Pump: ON"));
        }
    }
    
    // Stop watering
    void stopWatering() {
        if (pumpManager != nullptr) {
            if (isWatering()) {
                Serial.println(F("Pump: OFF"));
                pumpManager->turnOff();
            }
            // Zawsze aktualizuj czas ostatniego podlewania, nawet jeśli pompa już była wyłączona
            lastWateringTime = millis();
        }
    }
};

#endif // IRRIGATION_SERVICE_H 