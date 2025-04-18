#include "RgbLed.h"
#include "Photoresistor.h"

Photoresistor photoresistor(A0);
RgbLed rgbLed(9, 10, 11); // Assuming pins 9, 10, 11 for red, green, blue

void setup() {
  Serial.begin(9600);
}

void loop() {
  float lightValue = photoresistor.readValue();

  // Turn on blue if light value is between 30 and 50
  if (lightValue >= 55) {
    rgbLed.colorVariation(30, 30, 10);
    delay(1000);
    rgbLed.allOff();
  }

  // Turn on red if light value is more than 50
  if (lightValue > 25 && lightValue < 55) {
    rgbLed.colorVariation(127, 127, 50);
    delay(1000);
    rgbLed.allOff();
  }

  // Turn on red if light value is more than 50
  if (lightValue < 25) {
    rgbLed.colorVariation(255, 255, 255);
    delay(1000);
    rgbLed.allOff();
  }

  Serial.print("Light level: ");
  Serial.print(lightValue);
  Serial.print("%");
  Serial.println();
}