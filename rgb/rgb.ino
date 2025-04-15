#include "RgbLight.h"
#include "Photoresistor.h"
#include "TempSensor.h"

Photoresistor photoresistor(A0);

void setup() {
  Serial.begin(9600);

}

void loop() {
  float lightValue = photoresistor.readValue();

  // Turn on blue if light value is between 30 and 50
  if (lightValue >= 55) {
    rgbLight.colorVariation(30, 30, 10);
    delay(1000);
    rgbLight.allOff();
  }

  // Turn on red if light value is more than 50
  if (lightValue > 25 && lightValue < 55) {
    rgbLight.colorVariation(127, 127, 50);
    delay(1000);
    rgbLight.allOff();
  }

  // Turn on red if light value is more than 50
  if (lightValue < 25) {
    rgbLight.colorVariation(255, 255, 255);
    delay(1000);
    rgbLight.allOff();
  }

  Serial.print("Light level: ");
  Serial.print(lightValue);
  Serial.print("%");
  Serial.println();

  Serial.print("Current temperature: ");
  Serial.print(tempSensor.readTemperature());
  Serial.print("C");
  Serial.println();
}