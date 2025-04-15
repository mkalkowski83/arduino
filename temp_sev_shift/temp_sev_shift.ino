#include "TempSensor.h"
#include "DisplayManager.h"
#include "TemperatureDisplay.h"

TempSensor tempSensor(A0);
    
// Display 0000 on 4-digit 7-segment display with 74HC595 shift register
// For common anode display

// Define pins for shift register
#define SHIFT_PIN_DS 4      // DS
#define SHIFT_PIN_SHCP 6     // SHCP
#define SHIFT_PIN_STCP 5     // STCP

// Define pins for common display pins
#define DIGIT_1 12
#define DIGIT_2 11
#define DIGIT_3 10
#define DIGIT_4 9

byte digitPins[] = {DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4};

DisplayManager display(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP, digitPins);
TemperatureDisplay tempDisplay(tempSensor, display);

void setup() {
  Serial.begin(9600);
  tempDisplay.begin();
}

void loop() {
  tempDisplay.update();
}

