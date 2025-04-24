# LCD Thermometer

A versatile Arduino project that displays temperature and humidity readings from an AM2302/DHT22 sensor on an LCD display.

## Overview

This project creates a temperature and humidity monitoring system using:
- AM2302/DHT22 temperature and humidity sensor
- LCD display (16x2 characters)
- Arduino board

The code is structured using object-oriented programming principles with separate controller classes for different functionalities.

## Hardware Requirements

- Arduino board (Uno, Nano, Mega, etc.)
- AM2302/DHT22 temperature and humidity sensor
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

## Installation

1. Install the required libraries via the Arduino Library Manager
2. Copy the project files to your Arduino sketchbook folder
3. Open the LcdThermometer.ino sketch in the Arduino IDE
4. Adjust pin configurations if necessary
5. Upload the sketch to your Arduino board

## Usage

The main sketch (LcdThermometer.ino) initializes all required components and updates the display every 2 seconds with temperature and humidity readings.

### Example Sketch

```cpp
#include "controller/AM2302LcdController.h"
#include "utils/LcdManager.h"
#include "utils/AM2302Sensor.h"
#include "utils/SerialPortManager.h"

// Create LCD manager (pins: RS, E, D4, D5, D6, D7)
LcdManager lcdManager(12, 11, 5, 4, 3, 2);

// Create AM2302 sensor (data pin: 8)
AM2302Sensor am2302Sensor(8);

// Create serial manager with baud rate
SerialPortManager serialManager(9600);

// Create controller with all components
AM2302LcdController am2302LcdController(&lcdManager, &am2302Sensor, serialManager);

void setup() {
  // Initialize the controller (which initializes all components)
  am2302LcdController.begin();
}

void loop() {
  // Update the controller (reads sensor and updates display)
  am2302LcdController.update();
}
```

## Customization

You can customize the project by:
- Changing the update interval in the AM2302LcdController constructor
- Modifying the display format in the AM2302LcdController class
- Adding additional sensors or controllers

## Troubleshooting

If you encounter issues:
1. Check your wiring connections
2. Verify the serial output for debugging information
3. Ensure the AM2302/DHT22 sensor is properly powered
4. Try using a different data pin for the sensor

## License

This project is open source and available under the MIT License. 