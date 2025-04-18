#include "TempSensor.h"
#include "DisplayManager.h"
#include "TemperatureDisplayController.h"
#include "RgbLed.h"
#include "TemperatureColorController.h"
#include "SystemCoordinator.h"
#include "Controller.h"

#define RED_LED_PIN 2
#define BLUE_LED_PIN 3
#define GREEN_LED_PIN 7

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
#define TEMP_LOW 36.6       // Normal temperature - Green
#define TEMP_MEDIUM 37.0    // Mild fever - Yellow
#define TEMP_HIGH 38.0      // Moderate fever - Blue
#define TEMP_VERY_HIGH 39.0 // High fever - Red

// Define timing constants
#define COLOR_UPDATE_INTERVAL 5000   // Update color every 5 seconds

byte digitPins[] = { DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4 };

// Create component objects
RgbLed rgbLed(RED_LED_PIN, BLUE_LED_PIN, GREEN_LED_PIN);
TempSensor tempSensor(A0);

DisplayManager display(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP, digitPins);

TemperatureDisplayController tempDisplayController(tempSensor, display);
TemperatureColorController colorController(tempSensor, rgbLed, 
    TEMP_LOW, TEMP_MEDIUM, TEMP_HIGH, TEMP_VERY_HIGH, COLOR_UPDATE_INTERVAL);

// Create system coordinator
SystemCoordinator systemCoordinator;

void setup() {
  Serial.begin(9600);
  
  // Add controllers to the coordinator
  // Both controllers now handle their own timing internally
  systemCoordinator.addControllerAlways(&tempDisplayController);
  systemCoordinator.addControllerAlways(&colorController);
  
  // Initialize all controllers
  systemCoordinator.begin();
}

void loop() {
  // Update all controllers
  systemCoordinator.update();
}
