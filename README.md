# Kolekcja Projektów Arduino / Arduino Projects Collection

[English version below](#arduino-projects-collection)

Ten repozytorium zawiera zbiór różnych projektów Arduino, które demonstrują różne zastosowania i funkcjonalności. Każdy projekt jest niezależny i pokazuje inne aspekty programowania mikrokontrolerów.

## Projekty

### 1. Wyświetlacz Temperatury (temp_sev_shift)
Projekt wyświetlacza temperatury na wyświetlaczu 7-segmentowym. [Szczegółowa dokumentacja projektu](temp_sev_shift/README.md)

### 2. Sygnalizacja Świetlna (street_lights)
- Symuluje działanie sygnalizacji świetlnej na skrzyżowaniu
- Zawiera światła dla samochodów (czerwone, żółte, zielone)
- Obsługuje przejście dla pieszych z przyciskiem
- Implementuje logikę zmiany świateł i bezpieczne przejścia

### 3. Sterowanie RGB (rgb)
- Kontroluje diodę RGB
- Reaguje na poziom oświetlenia z fotorezystora
- Umożliwia tworzenie różnych efektów świetlnych
- Zawiera funkcje tęczy i płynnych przejść kolorów

### 4. Licznik (Counter)
- Prosty licznik wyświetlający wartości na wyświetlaczu 7-segmentowym
- Wykorzystuje bibliotekę SevSeg do sterowania wyświetlaczem
- Automatyczne zliczanie z możliwością resetowania

### 5. Licznik z Rejestrem Przesuwnym (Counter_shift_register)
- Podobny do projektu Counter, ale wykorzystuje rejestr przesuwny 74HC595
- Demonstracja sterowania wyświetlaczem 7-segmentowym przez rejestr przesuwny

### 6. Termometr LCD (LcdThermometer)
- Wyświetla temperaturę i wilgotność na wyświetlaczu LCD 16x2
- Wykorzystuje czujnik AM2302/DHT22
- Implementuje strukturę MVC z wzorcami projektowymi
- Wykorzystuje szereg klas narzędziowych do zarządzania komponentami
- [Szczegółowa dokumentacja projektu](LcdThermometer/README.md) (dostępna również [po polsku](LcdThermometer/README_PL.md))

## Biblioteki Narzędziowe (libraries/utils)

Projekt zawiera zestaw własnych bibliotek ułatwiających pracę z różnymi komponentami:

- `Button.h` - obsługa przycisków
- `DisplayManager.h` - zarządzanie wyświetlaczem 7-segmentowym
- `Photoresistor.h` - obsługa fotorezystora
- `TemperatureSensor.h` - obsługa czujnika temperatury
- `RgbLed.h` - sterowanie diodą RGB
- `PedestrianLight.h` - obsługa świateł dla pieszych
- `TrafficLight.h` - obsługa sygnalizacji świetlnej
- `Controller.h` - interfejs dla kontrolerów w systemie
- `TimedExecutor.h` - zarządzanie operacjami wykonywanymi w określonych interwałach czasowych
- `SystemCoordinator.h` - koordynator działania kontrolerów w systemie
- `SerialPortManager.h` - klasa zarządzająca komunikacją przez port szeregowy, zapewniająca bezpieczną inicjalizację i
  wygodne metody do wysyłania danych
- `LcdManager.h` - zarządzanie wyświetlaczem LCD
- `AM2302Sensor.h` - obsługa czujnika temperatury i wilgotności AM2302/DHT22
- `SoilMoistureSensor.h` - obsługa czujnika wilgotności gleby
- `PumpManager.h` - zarządzanie pompą wody do automatycznego nawadniania

## Nowe Klasy i Ich Użycie

### Wzorzec Projektowy MVC i Struktura Kontrolerów

Projekt wykorzystuje architekturę opartą na wzorcu Model-View-Controller (MVC) oraz wzorce projektowe takie jak Composite i Observer. Oto opis głównych klas:

### Controller.h
Abstrakcyjny interfejs dla wszystkich kontrolerów w systemie. Definiuje metody:
```cpp
virtual void begin() = 0;   // Inicjalizacja kontrolera
virtual void update() = 0;  // Aktualizacja stanu kontrolera
virtual const char* getName() { return "GenericController"; }  // Nazwa kontrolera
```

Użycie:
```cpp
class MyController : public Controller {
public:
    void begin() override { /* inicjalizacja */ }
    void update() override { /* aktualizacja */ }
    const char* getName() override { return "MyController"; }
};
```

### TimedExecutor.h
Klasa zarządzająca operacjami wykonywanymi w określonych odstępach czasu.
```cpp
TimedExecutor executor(1000); // Utworzenie z interwałem 1000ms
if (executor.shouldExecute()) {
    // Wykonaj operację co 1000ms
}
```

### TemperatureDisplayController.h
Kontroluje wyświetlanie temperatury na wyświetlaczu 7-segmentowym.
```cpp
TemperatureDisplayController tempDisplay(tempSensor, display);
tempDisplay.begin();  // Inicjalizacja
tempDisplay.update(); // Aktualizacja wyświetlacza
```

### TemperatureColorController.h
Steruje kolorem diody LED RGB w zależności od temperatury.
```cpp
TemperatureColorController colorCtrl(tempSensor, rgbLed, 
    36.6, // temperatura niska - zielony
    37.0, // średnia - żółty
    38.0, // wysoka - niebieski
    39.0  // bardzo wysoka - czerwony
);
colorCtrl.begin();
colorCtrl.update();
```

### RgbLed.h
Steruje diodą RGB z dodatkowymi efektami świetlnymi.
```cpp
RgbLed led(RED_PIN, GREEN_PIN, BLUE_PIN);
led.turnOnRed();    // Czerwony
led.turnOnGreen();  // Zielony
led.turnOnBlue();   // Niebieski
led.turnOnYellow(); // Żółty (czerwony + zielony)
led.rainbow(1, 5);  // Efekt tęczy
```

### SystemCoordinator.h
Koordynator zarządzający wieloma kontrolerami.
```cpp
SystemCoordinator coordinator;
coordinator.addController(&myController); // Dodanie kontrolera
coordinator.begin(); // Inicjalizacja wszystkich kontrolerów
coordinator.update(); // Aktualizacja wszystkich kontrolerów
```

### AM2302LcdController.h
Kontroler integrujący czujnik AM2302/DHT22 z wyświetlaczem LCD.
```cpp
LcdManager lcdManager(12, 11, 5, 4, 3, 2); // Pins: RS, E, D4, D5, D6, D7
AM2302Sensor sensor(8); // Data pin
SerialPortManager serialManager(9600);
AM2302LcdController controller(&lcdManager, &sensor, serialManager);
controller.begin();
controller.update();
```

## Wymagania

- Arduino IDE
- Płytka Arduino (testowane na Arduino Uno)
- Biblioteki:
  - OneWire
  - DallasTemperature
  - SevSeg
  - LiquidCrystal
  - Grove_Temperature_And_Humidity_Sensor

## Instalacja

1. Sklonuj repozytorium
2. Zainstaluj wymagane biblioteki przez Arduino Library Manager
3. Otwórz wybrany projekt w Arduino IDE
4. Wgraj kod do płytki Arduino

## Schemat Połączeń

Każdy projekt zawiera własne wymagania sprzętowe. Szczegółowe informacje o połączeniach można znaleźć w kodzie źródłowym poszczególnych projektów w postaci komentarzy przy definicjach pinów.

## Licencja

Ten projekt jest dostępny na licencji MIT. Możesz go swobodnie wykorzystywać, modyfikować i rozpowszechniać.

---

# Arduino Projects Collection

This repository contains a collection of various Arduino projects that demonstrate different applications and functionalities. Each project is independent and showcases different aspects of microcontroller programming.

## Projects

### 1. Temperature Display (temp_sev_shift)
Temperature display project using a 7-segment display. [Detailed project documentation](temp_sev_shift/README.md)

### 2. Traffic Lights (street_lights)
- Simulates traffic light operation at an intersection
- Includes car traffic lights (red, yellow, green)
- Handles pedestrian crossing with button input
- Implements light change logic and safe crossing sequences

### 3. RGB Control (rgb)
- Controls RGB LED
- Responds to light levels using a photoresistor
- Enables various lighting effects
- Includes rainbow and smooth color transition functions

### 4. Counter (Counter)
- Simple counter displaying values on a 7-segment display
- Uses SevSeg library for display control
- Automatic counting with reset capability

### 5. Counter with Shift Register (Counter_shift_register)
- Similar to Counter project but uses 74HC595 shift register
- Demonstrates 7-segment display control through shift register

### 6. LCD Thermometer (LcdThermometer)
- Displays temperature and humidity on a 16x2 LCD display
- Uses AM2302/DHT22 sensor
- Implements MVC structure with design patterns
- Uses various utility classes for component management
- [Detailed project documentation](LcdThermometer/README.md) (also available [in Polish](LcdThermometer/README_PL.md))

## Utility Libraries (libraries/utils)

The project includes a set of custom libraries to facilitate work with various components:

- `Button.h` - button handling
- `DisplayManager.h` - 7-segment display management
- `Photoresistor.h` - photoresistor handling
- `TemperatureSensor.h` - temperature sensor handling
- `RgbLed.h` - RGB LED control
- `PedestrianLight.h` - pedestrian light handling
- `TrafficLight.h` - traffic light handling
- `Controller.h` - interface for system controllers
- `TimedExecutor.h` - managing operations at specified time intervals
- `SystemCoordinator.h` - system controller coordinator
- `SerialPortManager.h` - class managing serial port communication, providing safe initialization and convenient methods
  for sending data
- `LcdManager.h` - LCD display management
- `AM2302Sensor.h` - AM2302/DHT22 temperature and humidity sensor handling
- `SoilMoistureSensor.h` - soil moisture sensor handling
- `PumpManager.h` - water pump management for automatic watering

## New Classes and Their Usage

### MVC Design Pattern and Controller Structure

The project uses an architecture based on the Model-View-Controller (MVC) pattern and design patterns such as Composite and Observer. Here's a description of the main classes:

### Controller.h
Abstract interface for all controllers in the system. Defines methods:
```cpp
virtual void begin() = 0;   // Controller initialization
virtual void update() = 0;  // Controller state update
virtual const char* getName() { return "GenericController"; }  // Controller name
```

Usage:
```cpp
class MyController : public Controller {
public:
    void begin() override { /* initialization */ }
    void update() override { /* update */ }
    const char* getName() override { return "MyController"; }
};
```

### TimedExecutor.h
Class managing operations performed at specified time intervals.
```cpp
TimedExecutor executor(1000); // Create with 1000ms interval
if (executor.shouldExecute()) {
    // Execute operation every 1000ms
}
```

### TemperatureDisplayController.h
Controls temperature display on a 7-segment display.
```cpp
TemperatureDisplayController tempDisplay(tempSensor, display);
tempDisplay.begin();  // Initialization
tempDisplay.update(); // Update display
```

### TemperatureColorController.h
Controls RGB LED color based on temperature.
```cpp
TemperatureColorController colorCtrl(tempSensor, rgbLed, 
    36.6, // low temperature - green
    37.0, // medium - yellow
    38.0, // high - blue
    39.0  // very high - red
);
colorCtrl.begin();
colorCtrl.update();
```

### RgbLed.h
Controls RGB LED with additional lighting effects.
```cpp
RgbLed led(RED_PIN, GREEN_PIN, BLUE_PIN);
led.turnOnRed();    // Red
led.turnOnGreen();  // Green
led.turnOnBlue();   // Blue
led.turnOnYellow(); // Yellow (red + green)
led.rainbow(1, 5);  // Rainbow effect
```

### SystemCoordinator.h
Coordinator managing multiple controllers.
```cpp
SystemCoordinator coordinator;
coordinator.addController(&myController); // Add controller
coordinator.begin(); // Initialize all controllers
coordinator.update(); // Update all controllers
```

### AM2302LcdController.h
Controller integrating AM2302/DHT22 sensor with LCD display.
```cpp
LcdManager lcdManager(12, 11, 5, 4, 3, 2); // Pins: RS, E, D4, D5, D6, D7
AM2302Sensor sensor(8); // Data pin
SerialPortManager serialManager(9600);
AM2302LcdController controller(&lcdManager, &sensor, serialManager);
controller.begin();
controller.update();
```

## Requirements

- Arduino IDE
- Arduino Board (tested on Arduino Uno)
- Libraries:
  - OneWire
  - DallasTemperature
  - SevSeg
  - LiquidCrystal
  - Grove_Temperature_And_Humidity_Sensor

## Installation

1. Clone the repository
2. Install required libraries through Arduino Library Manager
3. Open desired project in Arduino IDE
4. Upload code to Arduino board

## Wiring Diagrams

Each project has its own hardware requirements. Detailed connection information can be found in the source code of individual projects in the form of comments near pin definitions.

## License

This project is available under the MIT License. You can freely use, modify, and distribute it. 