#include <LcdManager.h>
#include <AM2302Sensor.h>
#include <SoilMoistureSensor.h>
#include <SystemCoordinator.h>

#include "controller/EnvironmentSensorLcdController.h"
#include "query/SensorReadQuery.h"

#define LCD_D7_PIN 2
#define LCD_D6_PIN 3
#define LCD_D5_PIN 4
#define LCD_D4_PIN 5
#define LCD_E_PIN 11
#define LCD_RS_PIN 12

#define TEMPERATURE_SENSOR_PIN 8
#define SOIL_MOISTURE_SENSOR_PIN A0

// #define RED_LED_PIN 6

AM2302Sensor am2302Sensor(TEMPERATURE_SENSOR_PIN);
SoilMoistureSensor soilMoistureSensor(SOIL_MOISTURE_SENSOR_PIN);
LcdManager lcdManager(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
SensorReadQuery sensorQuery(&am2302Sensor, &soilMoistureSensor);
SerialPortManager serialPortManager;

EnvironmentSensorLcdController environmentController(&lcdManager, &sensorQuery, &serialPortManager);

SystemCoordinator systemCoordinator;

void setup(void) {
  systemCoordinator.addController(&environmentController);
  systemCoordinator.begin();
}

void loop(void) {
  systemCoordinator.update();
}