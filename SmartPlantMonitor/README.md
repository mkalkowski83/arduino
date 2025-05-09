# Smart Plant Monitor

A versatile Arduino project for monitoring and automatically watering plants, displaying temperature, air humidity, and
soil moisture readings on an LCD display.

## Overview

This project creates a plant monitoring and care system using:

- AM2302/DHT22 temperature and humidity sensor
- Soil moisture sensor
- Automatic watering system with pump
- LCD display (16x2 characters)
- Arduino board

The code is structured using object-oriented programming principles with separate controller classes for different
functionalities.

## Hardware Requirements

- Arduino board (Uno, Nano, Mega, etc.)
- AM2302/DHT22 temperature and humidity sensor
- Soil moisture sensor
- Water pump
- 16x2 LCD display
- Connecting wires
- Breadboard (optional)

## Wiring Instructions

### LCD Display

- RS pin to digital pin 12
- Enable pin to digital pin 11
- D4 pin to digital pin 5
- D5 pin to digital pin 4
- D6 pin to digital pin 3
- D7 pin to digital pin 2
- VSS to GND
- VDD to 5V
- V0 to potentiometer (for contrast adjustment)
- A to 5V (backlight)
- K to GND (backlight)

### AM2302/DHT22 Sensor

- VCC to 5V
- GND to GND
- DATA to digital pin 8 (can be changed in the code)

### Soil Moisture Sensor

- VCC to 5V
- GND to GND
- DATA to analog pin A0 (can be changed in the code)

### Water Pump

- VCC to collector (C) of NPN transistor
- GND to ground (GND)
- Emitter (E) of transistor connected to GND
- Base (B) of transistor connected to digital pin 7 through a 4.3K resistor
- Protection diode 1N4001 in parallel with the pump (cathode to VCC, anode to collector)

## Software Requirements

### Libraries

- Grove_Temperature_And_Humidity_Sensor
- LiquidCrystal

### Project Classes

- **AM2302Sensor**: Wrapper for the AM2302/DHT22 sensor
- **LcdManager**: Handles LCD display operations
- **AM2302LcdController**: Controller that integrates sensor and display
- **SerialPortManager**: Handles serial communication
- **TimedExecutor**: Manages timed operations
- **SoilMoistureSensor**: Handles soil moisture sensor
- **PumpManager**: Manages water pump for automatic watering

## Installation

1. Install the required libraries via the Arduino Library Manager
2. Copy the project files to your Arduino sketchbook folder
3. Open the SmartPlantMonitor.ino sketch in the Arduino IDE
4. Adjust pin configurations if necessary
5. Upload the sketch to your Arduino board

## Usage

The main sketch (SmartPlantMonitor.ino) initializes all required components and updates the display with temperature,
air humidity, and soil moisture readings. The system automatically activates the pump when the soil moisture level falls
below a set threshold.

### Example Sketch

```cpp
#include "controller/AM2302LcdController.h"
#include "utils/LcdManager.h"
#include "utils/AM2302Sensor.h"
#include "utils/SerialPortManager.h"
#include "utils/SoilMoistureSensor.h"
#include "utils/PumpManager.h"

// Create LCD manager (pins: RS, E, D4, D5, D6, D7)
LcdManager lcdManager(12, 11, 5, 4, 3, 2);

// Create AM2302 sensor (data pin: 8)
AM2302Sensor am2302Sensor(8);

// Create soil moisture sensor (analog pin: A0)
SoilMoistureSensor soilSensor(A0);

// Create pump manager (control pin: 7)
PumpManager pumpManager(7);

// Create serial manager with baud rate
SerialPortManager serialManager(9600);

// Create controller with all components
AM2302LcdController am2302LcdController(&lcdManager, &am2302Sensor, serialManager);

void setup() {
  // Initialize the controller (which initializes all components)
  am2302LcdController.begin();
  soilSensor.begin();
  pumpManager.begin();
}

void loop() {
  // Update controllers
  am2302LcdController.update();
  
  // Check soil moisture and control pump
  int soilMoisture = soilSensor.readMoisture();
  if (soilMoisture < 30) { // If moisture < 30%
    pumpManager.startPump(3000); // Run pump for 3 seconds
  }
}
```

## Customization

You can customize the project by:

- Changing the update interval in controller constructors
- Modifying the soil moisture threshold for pump activation
- Modifying the display format in the LCD controller class
- Adding additional sensors or controllers

## Troubleshooting

If you encounter issues:

1. Check your wiring connections
2. Verify the serial output for debugging information
3. Ensure the sensors are properly powered
4. Check if the pump is correctly connected

## License

This project is open source and available under the MIT License. 