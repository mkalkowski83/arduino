# Termometr LCD

Wszechstronny projekt Arduino wyświetlający odczyty temperatury i wilgotności z czujnika AM2302/DHT22 na wyświetlaczu LCD.

## Przegląd

Ten projekt tworzy system monitorowania temperatury i wilgotności wykorzystujący:
- Czujnik temperatury i wilgotności AM2302/DHT22
- Wyświetlacz LCD (16x2 znaki)
- Płytkę Arduino

Kod jest zorganizowany zgodnie z zasadami programowania obiektowego, z oddzielnymi klasami kontrolerów dla różnych funkcjonalności.

## Wymagania sprzętowe

- Płytka Arduino (Uno, Nano, Mega, itp.)
- Czujnik temperatury i wilgotności AM2302/DHT22
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

## Instalacja

1. Zainstaluj wymagane biblioteki przez Menedżer Bibliotek Arduino
2. Skopiuj pliki projektu do folderu szkiców Arduino
3. Otwórz szkic LcdThermometer.ino w IDE Arduino
4. Dostosuj konfigurację pinów, jeśli to konieczne
5. Wgraj szkic na płytkę Arduino

## Użytkowanie

Główny szkic (LcdThermometer.ino) inicjalizuje wszystkie wymagane komponenty i aktualizuje wyświetlacz co 2 sekundy z odczytami temperatury i wilgotności.

### Przykładowy szkic

```cpp
#include "controller/AM2302LcdController.h"
#include "utils/LcdManager.h"
#include "utils/AM2302Sensor.h"
#include "utils/SerialPortManager.h"

// Tworzenie menedżera LCD (piny: RS, E, D4, D5, D6, D7)
LcdManager lcdManager(12, 11, 5, 4, 3, 2);

// Tworzenie czujnika AM2302 (pin danych: 8)
AM2302Sensor am2302Sensor(8);

// Tworzenie menedżera portu szeregowego z prędkością transmisji
SerialPortManager serialManager(9600);

// Tworzenie kontrolera ze wszystkimi komponentami
AM2302LcdController am2302LcdController(&lcdManager, &am2302Sensor, serialManager);

void setup() {
  // Inicjalizacja kontrolera (który inicjalizuje wszystkie komponenty)
  am2302LcdController.begin();
}

void loop() {
  // Aktualizacja kontrolera (odczyt czujnika i aktualizacja wyświetlacza)
  am2302LcdController.update();
}
```

## Dostosowywanie

Możesz dostosować projekt poprzez:
- Zmianę interwału aktualizacji w konstruktorze AM2302LcdController
- Modyfikację formatu wyświetlania w klasie AM2302LcdController
- Dodanie dodatkowych czujników lub kontrolerów

## Rozwiązywanie problemów

Jeśli napotkasz problemy:
1. Sprawdź połączenia przewodów
2. Zweryfikuj dane wyjściowe portu szeregowego w celu debugowania
3. Upewnij się, że czujnik AM2302/DHT22 jest prawidłowo zasilany
4. Spróbuj użyć innego pinu danych dla czujnika

## Licencja

Ten projekt jest otwartoźródłowy i dostępny na licencji MIT. 