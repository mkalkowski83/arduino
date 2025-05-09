# Smart Plant Monitor

Wszechstronny projekt Arduino do monitorowania i automatycznego nawadniania roślin, wyświetlający odczyty temperatury,
wilgotności powietrza i wilgotności gleby na wyświetlaczu LCD.

## Przegląd

Ten projekt tworzy system monitorowania i pielęgnacji roślin wykorzystujący:

- Czujnik temperatury i wilgotności AM2302/DHT22
- Czujnik wilgotności gleby
- System automatycznego nawadniania z pompą
- Wyświetlacz LCD (16x2 znaki)
- Płytkę Arduino

Kod jest zorganizowany zgodnie z zasadami programowania obiektowego, z oddzielnymi klasami kontrolerów dla różnych
funkcjonalności.

## Wymagania sprzętowe

- Płytka Arduino (Uno, Nano, Mega, itp.)
- Czujnik temperatury i wilgotności AM2302/DHT22
- Czujnik wilgotności gleby
- Pompa wodna
- Wyświetlacz LCD 16x2
- Przewody połączeniowe
- Płytka prototypowa (opcjonalnie)

## Instrukcje podłączenia

### Wyświetlacz LCD

- Pin RS do pinu cyfrowego 12
- Pin Enable do pinu cyfrowego 11
- Pin D4 do pinu cyfrowego 5
- Pin D5 do pinu cyfrowego 4
- Pin D6 do pinu cyfrowego 3
- Pin D7 do pinu cyfrowego 2
- VSS do GND
- VDD do 5V
- V0 do potencjometru (do regulacji kontrastu)
- A do 5V (podświetlenie)
- K do GND (podświetlenie)

### Czujnik AM2302/DHT22

- VCC do 5V
- GND do GND
- DATA do pinu cyfrowego 8 (może być zmieniony w kodzie)

### Czujnik wilgotności gleby

- VCC do 5V
- GND do GND
- DATA do pinu analogowego A0 (może być zmieniony w kodzie)

### Pompa wodna

- VCC do kolektora (C) tranzystora NPN
- GND do masy (GND)
- Emiter (E) tranzystora podłączony do GND
- Baza (B) tranzystora podłączona do pinu cyfrowego 7 przez rezystor 4,3K
- Dioda zabezpieczająca 1N4001 równolegle do pompy (katoda do VCC, anoda do kolektora)

## Wymagania programowe

### Biblioteki

- Grove_Temperature_And_Humidity_Sensor
- LiquidCrystal

### Klasy projektu

- **AM2302Sensor**: Wrapper dla czujnika AM2302/DHT22
- **LcdManager**: Obsługuje operacje wyświetlacza LCD
- **AM2302LcdController**: Kontroler integrujący czujnik i wyświetlacz
- **SerialPortManager**: Obsługuje komunikację szeregową
- **TimedExecutor**: Zarządza operacjami wykonywanymi w określonych odstępach czasu
- **SoilMoistureSensor**: Obsługuje czujnik wilgotności gleby
- **PumpManager**: Zarządza pompą wody do automatycznego nawadniania

## Instalacja

1. Zainstaluj wymagane biblioteki przez Menedżer Bibliotek Arduino
2. Skopiuj pliki projektu do folderu szkiców Arduino
3. Otwórz szkic SmartPlantMonitor.ino w IDE Arduino
4. Dostosuj konfigurację pinów, jeśli to konieczne
5. Wgraj szkic na płytkę Arduino

## Użytkowanie

Główny szkic (SmartPlantMonitor.ino) inicjalizuje wszystkie wymagane komponenty i aktualizuje wyświetlacz z odczytami
temperatury, wilgotności powietrza i wilgotności gleby. System automatycznie uruchamia pompę, gdy poziom wilgotności
gleby spada poniżej ustawionego progu.

### Przykładowy szkic

```cpp
#include "controller/AM2302LcdController.h"
#include "utils/LcdManager.h"
#include "utils/AM2302Sensor.h"
#include "utils/SerialPortManager.h"
#include "utils/SoilMoistureSensor.h"
#include "utils/PumpManager.h"

// Tworzenie menedżera LCD (piny: RS, E, D4, D5, D6, D7)
LcdManager lcdManager(12, 11, 5, 4, 3, 2);

// Tworzenie czujnika AM2302 (pin danych: 8)
AM2302Sensor am2302Sensor(8);

// Tworzenie czujnika wilgotności gleby (pin analogowy: A0)
SoilMoistureSensor soilSensor(A0);

// Tworzenie menedżera pompy (pin sterujący: 7)
PumpManager pumpManager(7);

// Tworzenie menedżera portu szeregowego z prędkością transmisji
SerialPortManager serialManager(9600);

// Tworzenie kontrolera ze wszystkimi komponentami
AM2302LcdController am2302LcdController(&lcdManager, &am2302Sensor, serialManager);

void setup() {
  // Inicjalizacja kontrolera (który inicjalizuje wszystkie komponenty)
  am2302LcdController.begin();
  soilSensor.begin();
  pumpManager.begin();
}

void loop() {
  // Aktualizacja kontrolerów
  am2302LcdController.update();
  
  // Sprawdzenie wilgotności gleby i sterowanie pompą
  int soilMoisture = soilSensor.readMoisture();
  if (soilMoisture < 30) { // Jeśli wilgotność < 30%
    pumpManager.startPump(3000); // Włącz pompę na 3 sekundy
  }
}
```

## Dostosowywanie

Możesz dostosować projekt poprzez:

- Zmianę interwału aktualizacji w konstruktorach kontrolerów
- Modyfikację progu wilgotności gleby dla uruchomienia pompy
- Modyfikację formatu wyświetlania w klasie kontrolera LCD
- Dodanie dodatkowych czujników lub kontrolerów

## Rozwiązywanie problemów

Jeśli napotkasz problemy:

1. Sprawdź połączenia przewodów
2. Zweryfikuj dane wyjściowe portu szeregowego w celu debugowania
3. Upewnij się, że czujniki są prawidłowo zasilane
4. Sprawdź czy pompa jest prawidłowo podłączona

## Licencja

Ten projekt jest otwartoźródłowy i dostępny na licencji MIT. 