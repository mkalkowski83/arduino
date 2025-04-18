# Wyświetlacz Temperatury z Rejestrem Przesuwnym / Temperature Display with Shift Register

[English version below](#temperature-display-with-shift-register)

## Opis
Projekt wyświetlacza temperatury wykorzystującego cyfrowy czujnik temperatury DS18B20 oraz wyświetlacz 7-segmentowy sterowany przez rejestr przesuwny 74HC595. Dodatkowo zawiera diodę RGB, która zmienia kolor w zależności od zmierzonej temperatury.

Schematy komponentów:
- Rejestr przesuwny: [74HC595_pinout.txt](../assets/74HC595_pinout.txt)
- Wyświetlacz 7-segmentowy: [4digit_7segment_display.txt](../assets/4digit_7segment_display.txt)

## Komponenty Elektroniczne
1. Arduino Uno/Nano
2. Wyświetlacz 7-segmentowy 4-cyfrowy (wspólna anoda)
3. Rejestr przesuwny 74HC595
4. Czujnik temperatury DS18B20
5. Dioda RGB (wspólna katoda)
6. Rezystory:
   - 4.7kΩ x 1 (dla czujnika DS18B20)
   - 220Ω x 4 (dla pinów wspólnej anody wyświetlacza)
   - 220Ω x 3 (dla każdej nóżki diody RGB)
7. Przewody połączeniowe
8. Płytka stykowa (breadboard)

## Schemat Połączeń

### Czujnik DS18B20:
- PIN VCC -> Arduino 5V
- PIN GND -> Arduino GND
- PIN DATA -> Arduino A0
- Rezystor podciągający 4.7kΩ między VCC a DATA

### Rejestr Przesuwny 74HC595:
- PIN 1 (Q1) -> Segment A wyświetlacza
- PIN 2 (Q2) -> Segment B wyświetlacza
- PIN 3 (Q3) -> Segment C wyświetlacza
- PIN 4 (Q4) -> Segment D wyświetlacza
- PIN 5 (Q5) -> Segment E wyświetlacza
- PIN 6 (Q6) -> Segment F wyświetlacza
- PIN 7 (Q7) -> Segment G wyświetlacza
- PIN 8 (GND) -> Arduino GND
- PIN 9 (Q7') -> Nie podłączony
- PIN 10 (MR) -> Arduino 5V
- PIN 11 (SHCP) -> Arduino PIN 6
- PIN 12 (STCP) -> Arduino PIN 5
- PIN 13 (OE) -> Arduino GND
- PIN 14 (DS) -> Arduino PIN 4
- PIN 15 (Q0) -> Segment DP wyświetlacza
- PIN 16 (VCC) -> Arduino 5V

### Wyświetlacz 7-segmentowy:
- Wspólne anody (DIGIT 1-4) -> poprzez rezystory 220Ω do Arduino PIN 12, 11, 10, 9
- Segmenty A-G, DP -> do odpowiednich pinów rejestru 74HC595

### Dioda RGB:
- PIN Czerwony -> poprzez rezystor 220Ω do Arduino PIN 2
- PIN Zielony -> poprzez rezystor 220Ω do Arduino PIN 7
- PIN Niebieski -> poprzez rezystor 220Ω do Arduino PIN 3
- PIN Wspólna katoda -> Arduino GND

## Wymagane Biblioteki
1. OneWire (dla DS18B20)
   - Instalacja: Arduino IDE -> Tools -> Manage Libraries -> Wyszukaj "OneWire"
   - Wersja: 2.3.7 lub nowsza

2. DallasTemperature (dla DS18B20)
   - Instalacja: Arduino IDE -> Tools -> Manage Libraries -> Wyszukaj "DallasTemperature"
   - Wersja: 3.9.0 lub nowsza

## Biblioteki Lokalne (zawarte w projekcie)
- `TempSensor.h` - obsługa czujnika temperatury
- `DisplayManager.h` - zarządzanie wyświetlaczem
- `RgbLed.h` - sterowanie diodą RGB
- `Controller.h` - interfejs dla kontrolerów w systemie
- `TemperatureDisplayController.h` - kontroler wyświetlania temperatury
- `TemperatureColorController.h` - kontroler kolorów LED zależnych od temperatury
- `TimedExecutor.h` - zarządzanie operacjami wykonywanymi w określonych interwałach czasowych
- `SystemCoordinator.h` - koordynator działania kontrolerów w systemie

## Architektura Aplikacji

Projekt wykorzystuje wzorzec projektowy Model-View-Controller (MVC) oraz inne wzorce projektowe jak Composite i Observer:

1. **Model**:
   - `TempSensor` - odczytuje temperaturę z czujnika DS18B20
   
2. **View**:
   - `DisplayManager` - zarządza wyświetlaczem 7-segmentowym
   - `RgbLed` - steruje diodą RGB
   
3. **Controller**:
   - `TemperatureDisplayController` - kontroluje wyświetlanie temperatury
   - `TemperatureColorController` - kontroluje kolor diody LED w zależności od temperatury
   - `SystemCoordinator` - koordynuje działanie wszystkich kontrolerów

4. **Utilities**:
   - `TimedExecutor` - zarządzanie operacjami wykonywanymi w określonych interwałach czasu
   - `Controller` - interfejs bazowy dla wszystkich kontrolerów

## Funkcjonalność

1. **Wyświetlanie Temperatury**:
   - Temperatura aktualizowana co 5 sekund
   - Wyświetlana z dokładnością do 0.01°C
   - Multipleksowanie wyświetlacza zapewnia płynne wyświetlanie

2. **Wskaźnik Temperatury LED**:
   - Zielony: normalna temperatura (<36.6°C)
   - Żółty: lekko podwyższona (36.6-37.0°C)
   - Niebieski: średnio podwyższona (37.0-38.0°C)
   - Żółty (ostrzegawczy): wysoka (38.0-39.0°C)
   - Czerwony: bardzo wysoka (>39.0°C)

## Konfiguracja
1. Zainstaluj wymagane biblioteki przez Arduino Library Manager
2. Podłącz komponenty według schematu połączeń
3. Wgraj kod do Arduino
4. Wyświetlacz powinien pokazać aktualną temperaturę, a dioda RGB zaświeci się odpowiednim kolorem

---

# Temperature Display with Shift Register

## Description
Temperature display project using a DS18B20 digital temperature sensor and a 7-segment display controlled by a 74HC595 shift register. Additionally, it includes an RGB LED that changes color based on the measured temperature.

Component diagrams:
- Shift register: [74HC595_pinout.txt](../assets/74HC595_pinout.txt)
- 7-segment display: [4digit_7segment_display.txt](../assets/4digit_7segment_display.txt)

## Electronic Components
1. Arduino Uno/Nano
2. 4-digit 7-segment display (common anode)
3. 74HC595 shift register
4. DS18B20 temperature sensor
5. RGB LED (common cathode)
6. Resistors:
   - 4.7kΩ x 1 (for DS18B20 sensor)
   - 220Ω x 4 (for display common anode pins)
   - 220Ω x 3 (for each RGB LED pin)
7. Connecting wires
8. Breadboard

## Wiring Diagram

### DS18B20 Sensor:
- VCC PIN -> Arduino 5V
- GND PIN -> Arduino GND
- DATA PIN -> Arduino A0
- 4.7kΩ pull-up resistor between VCC and DATA

### 74HC595 Shift Register:
- PIN 1 (Q1) -> Display Segment A
- PIN 2 (Q2) -> Display Segment B
- PIN 3 (Q3) -> Display Segment C
- PIN 4 (Q4) -> Display Segment D
- PIN 5 (Q5) -> Display Segment E
- PIN 6 (Q6) -> Display Segment F
- PIN 7 (Q7) -> Display Segment G
- PIN 8 (GND) -> Arduino GND
- PIN 9 (Q7') -> Not connected
- PIN 10 (MR) -> Arduino 5V
- PIN 11 (SHCP) -> Arduino PIN 6
- PIN 12 (STCP) -> Arduino PIN 5
- PIN 13 (OE) -> Arduino GND
- PIN 14 (DS) -> Arduino PIN 4
- PIN 15 (Q0) -> Display Segment DP
- PIN 16 (VCC) -> Arduino 5V

### 7-Segment Display:
- Common anodes (DIGIT 1-4) -> through 220Ω resistors to Arduino PINs 12, 11, 10, 9
- Segments A-G, DP -> to corresponding 74HC595 pins

### RGB LED:
- Red PIN -> through 220Ω resistor to Arduino PIN 2
- Green PIN -> through 220Ω resistor to Arduino PIN 7
- Blue PIN -> through 220Ω resistor to Arduino PIN 3
- Common cathode PIN -> Arduino GND

## Required Libraries
1. OneWire (for DS18B20)
   - Installation: Arduino IDE -> Tools -> Manage Libraries -> Search for "OneWire"
   - Version: 2.3.7 or newer

2. DallasTemperature (for DS18B20)
   - Installation: Arduino IDE -> Tools -> Manage Libraries -> Search for "DallasTemperature"
   - Version: 3.9.0 or newer

## Local Libraries (included in project)
- `TempSensor.h` - temperature sensor handling
- `DisplayManager.h` - display management
- `RgbLed.h` - RGB LED control
- `Controller.h` - interface for system controllers
- `TemperatureDisplayController.h` - temperature display controller
- `TemperatureColorController.h` - LED color controller based on temperature
- `TimedExecutor.h` - managing operations at specified time intervals
- `SystemCoordinator.h` - system controller coordinator

## Application Architecture

The project uses the Model-View-Controller (MVC) design pattern and other design patterns like Composite and Observer:

1. **Model**:
   - `TempSensor` - reads temperature from DS18B20 sensor
   
2. **View**:
   - `DisplayManager` - manages 7-segment display
   - `RgbLed` - controls RGB LED
   
3. **Controller**:
   - `TemperatureDisplayController` - controls temperature display
   - `TemperatureColorController` - controls LED color based on temperature
   - `SystemCoordinator` - coordinates all controllers

4. **Utilities**:
   - `TimedExecutor` - manages operations performed at specified time intervals
   - `Controller` - base interface for all controllers

## Functionality

1. **Temperature Display**:
   - Temperature updated every 5 seconds
   - Displayed with 0.01°C precision
   - Display multiplexing ensures smooth display

2. **LED Temperature Indicator**:
   - Green: normal temperature (<36.6°C)
   - Yellow: slightly elevated (36.6-37.0°C)
   - Blue: moderately elevated (37.0-38.0°C)
   - Yellow (warning): high (38.0-39.0°C)
   - Red: very high (>39.0°C)

## Setup
1. Install required libraries through Arduino Library Manager
2. Connect components according to the wiring diagram
3. Upload code to Arduino
4. Display should show current temperature, and RGB LED will light up with appropriate color 