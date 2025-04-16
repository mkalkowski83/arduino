# Wyświetlacz Temperatury z Rejestrem Przesuwnym / Temperature Display with Shift Register

[English version below](#temperature-display-with-shift-register)

## Opis
Projekt wyświetlacza temperatury wykorzystującego cyfrowy czujnik temperatury DS18B20 oraz wyświetlacz 7-segmentowy sterowany przez rejestr przesuwny 74HC595. 

Schematy komponentów:
- Rejestr przesuwny: [74HC595_pinout.txt](../assets/74HC595_pinout.txt)
- Wyświetlacz 7-segmentowy: [4digit_7segment_display.txt](../assets/4digit_7segment_display.txt)

## Komponenty Elektroniczne
1. Arduino Uno/Nano
2. Wyświetlacz 7-segmentowy 4-cyfrowy (wspólna anoda)
3. Rejestr przesuwny 74HC595
4. Czujnik temperatury DS18B20
5. Rezystory:
   - 4.7kΩ x 1 (dla czujnika DS18B20)
   - 220Ω x 4 (dla pinów wspólnej anody wyświetlacza)
6. Przewody połączeniowe
7. Płytka stykowa (breadboard)

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
- `TemperatureDisplay.h` - logika wyświetlania temperatury

## Konfiguracja
1. Zainstaluj wymagane biblioteki przez Arduino Library Manager
2. Podłącz komponenty według schematu połączeń
3. Wgraj kod do Arduino
4. Wyświetlacz powinien pokazać aktualną temperaturę z dokładnością do 0.01°C

---

# Temperature Display with Shift Register

## Description
Temperature display project using a DS18B20 digital temperature sensor and a 7-segment display controlled by a 74HC595 shift register.

Component diagrams:
- Shift register: [74HC595_pinout.txt](../assets/74HC595_pinout.txt)
- 7-segment display: [4digit_7segment_display.txt](../assets/4digit_7segment_display.txt)

## Electronic Components
1. Arduino Uno/Nano
2. 4-digit 7-segment display (common anode)
3. 74HC595 shift register
4. DS18B20 temperature sensor
5. Resistors:
   - 4.7kΩ x 1 (for DS18B20 sensor)
   - 220Ω x 4 (for display common anode pins)
6. Connecting wires
7. Breadboard

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
- `TemperatureDisplay.h` - temperature display logic

## Setup
1. Install required libraries through Arduino Library Manager
2. Connect components according to the wiring diagram
3. Upload code to Arduino
4. Display should show current temperature with 0.01°C precision 