#include "DisplayManager.h"
#include "RgbLed.h"
#include "Buzzer.h"
#include "TemperatureSensor.h"
#include "SystemCoordinator.h"
#include "SerialPortManager.h"

#include "controller/TemperatureBuzzerController.h"
#include "controller/TemperatureColorController.h"
#include "controller/TemperatureDisplayController.h"

#define RED_LED_PIN 2
#define BLUE_LED_PIN 3
#define GREEN_LED_PIN 7
#define BUZZER_PIN 8
#define TEMPERATURE_SENSOR_PIN A0
#define SERIAL_BAUD_RATE 9600

// Display 0000 on 4-digit 7-segment display with 74HC595 shift register
// For common anode display

// Define pins for shift register
#define SHIFT_PIN_DS 4    // DS
#define SHIFT_PIN_SHCP 6  // SHCP
#define SHIFT_PIN_STCP 5  // STCP

// Define pins for common display pins
#define DIGIT_1 12
#define DIGIT_2 11
#define DIGIT_3 10
#define DIGIT_4 9

// Define temperature thresholds
#define TEMP_LOW 22.0       // Normal temperature - Green
#define TEMP_MEDIUM 23.0    // Mild fever - Yellow
#define TEMP_HIGH 25.0      // Moderate fever - Blue
#define TEMP_VERY_HIGH 26.0 // High fever - Red

// Define timing constants
#define COLOR_UPDATE_INTERVAL 5000   // Update color every 5 seconds
#define BUZZER_CHECK_INTERVAL 5000   // Check temperature for buzzer every 3 seconds

byte digitPins[] = { DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4 };

// Create component objects
RgbLed rgbLed(RED_LED_PIN, BLUE_LED_PIN, GREEN_LED_PIN);
TemperatureSensor temperatureSensor(TEMPERATURE_SENSOR_PIN);
Buzzer buzzer(BUZZER_PIN);

DisplayManager display(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP, digitPins);

TemperatureDisplayController tempDisplayController(temperatureSensor, display);
TemperatureColorController colorController(temperatureSensor, rgbLed, TEMP_LOW, TEMP_MEDIUM, TEMP_HIGH, TEMP_VERY_HIGH, COLOR_UPDATE_INTERVAL);
TemperatureBuzzerController buzzerController(temperatureSensor, buzzer, TEMP_VERY_HIGH, BUZZER_CHECK_INTERVAL);
SerialPortManager serialManager(SERIAL_BAUD_RATE);

// Create system coordinator
SystemCoordinator systemCoordinator;

void setup() {
  // Initialize serial communication
  serialManager.begin();
  
  // Add controllers to the coordinator
  systemCoordinator.addController(&tempDisplayController);
  systemCoordinator.addController(&colorController);
  systemCoordinator.addController(&buzzerController);
  
  // Initialize all controllers
  systemCoordinator.begin();
}

void loop() {
  // Update all controllers
  systemCoordinator.update();
}
