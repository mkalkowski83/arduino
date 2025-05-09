#include <LcdManager.h>
#include <AM2302Sensor.h>
#include <SoilMoistureSensor.h>
#include <SystemCoordinator.h>
#include <PumpManager.h>

#include "controller/PumpController.h"
#include "controller/EnvironmentSensorLcdController.h"
#include "query/SensorReadQuery.h"

#include "service/IrrigationService.h"

#define LCD_D7_PIN 2
#define LCD_D6_PIN 3
#define LCD_D5_PIN 4
#define LCD_D4_PIN 5
#define LCD_E_PIN 11
#define LCD_RS_PIN 12

#define TEMPERATURE_SENSOR_PIN 8
#define SOIL_MOISTURE_SENSOR_PIN A0

#define PUMP_PIN 9

// #define RED_LED_PIN 6

AM2302Sensor am2302Sensor(TEMPERATURE_SENSOR_PIN);
SoilMoistureSensor soilMoistureSensor(SOIL_MOISTURE_SENSOR_PIN);
LcdManager lcdManager(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
SensorReadQuery sensorQuery(&am2302Sensor, &soilMoistureSensor);
PumpManager pumpManager(PUMP_PIN);
SerialPortManager serialPortManager;

// Create irrigation service with auto-watering enabled
IrrigationService irrigationService(
  &pumpManager, 
  &sensorQuery,
  5000,    // 5 seconds watering duration
  50,       // Start watering when moisture below 50%
  70,       // Stop watering when moisture reaches 70%
  true      // Auto-watering enabled
);

EnvironmentSensorLcdController environmentController(&lcdManager, &sensorQuery, &serialPortManager);
PumpController pumpController(&irrigationService);

SystemCoordinator systemCoordinator;

void setup(void) {
  Serial.begin(9600);
  systemCoordinator.addController(&environmentController);
  systemCoordinator.addController(&pumpController);
  systemCoordinator.begin();
}

void loop(void) {
  systemCoordinator.update();
}