#include "TempSensor.h"

TempSensor tempSensor(A0);

// Display 0000 on 4-digit 7-segment display with 74HC595 shift register
// For common anode display

// Define pins for shift register
#define DATA_PIN 4      // DS
#define CLOCK_PIN 6     // SHCP
#define LATCH_PIN 5     // STCP

// Define pins for common display pins
#define DIGIT_1 12
#define DIGIT_2 11
#define DIGIT_3 10
#define DIGIT_4 9

// Global variables for display
volatile byte currentDigit = 0;
volatile int numberToDisplay = 0;
volatile int decimalPos = 0;

// Segment patterns for common anode display (0 turns segment ON, 1 turns it OFF)
// Segments arranged as it is start right after binnary notation (0B) in this sequence: DP, G, F, E, D, C, B, A
const byte digits[] = {
  0B11000000,  // 0 
  0B11111001,  // 1
  0B10100100,  // 2
  0B10110000,  // 3
  0B10011001,  // 4
  0B10010010,  // 5
  0B10000010,  // 6
  0B11111000,  // 7
  0B10000000,  // 8
  0B10010000   // 9
};

// Send data to shift register - optimized version
void shiftOut(byte data) {
  digitalWrite(LATCH_PIN, LOW);
  
  for (int i = 7; i >= 0; i--) {
    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(DATA_PIN, bitRead(data, i));
    digitalWrite(CLOCK_PIN, HIGH);
  }
  
  digitalWrite(LATCH_PIN, HIGH);
}

// Timer1 interrupt service routine
ISR(TIMER1_COMPA_vect) {
  // Turn off all digits
  digitalWrite(DIGIT_1, LOW);
  digitalWrite(DIGIT_2, LOW);
  digitalWrite(DIGIT_3, LOW);
  digitalWrite(DIGIT_4, LOW);
  
  // Calculate the digit to display
  int digit;
  switch(currentDigit) {
    case 0:
      digit = (numberToDisplay / 1000) % 10;
      break;
    case 1:
      digit = (numberToDisplay / 100) % 10;
      break;
    case 2:
      digit = (numberToDisplay / 10) % 10;
      break;
    default:
      digit = numberToDisplay % 10;
      break;
  }
  
  // Get the pattern and add decimal point if needed
  byte pattern = digits[digit];
  if (decimalPos == (currentDigit + 1)) {
    pattern &= 0b01111111;
  }
  
  // Output the pattern
  shiftOut(pattern);
  
  // Turn on the current digit
  switch(currentDigit) {
    case 0:
      digitalWrite(DIGIT_1, HIGH);
      break;
    case 1:
      digitalWrite(DIGIT_2, HIGH);
      break;
    case 2:
      digitalWrite(DIGIT_3, HIGH);
      break;
    case 3:
      digitalWrite(DIGIT_4, HIGH);
      break;
  }
  
  // Move to next digit
  currentDigit = (currentDigit + 1) % 4;
}

void displayNumber(int number, int decimalPosition = 0) {
  numberToDisplay = constrain(number, 0, 9999);
  decimalPos = decimalPosition;
}

void setup() {
  Serial.begin(9600);
  
  // Set shift register pins as outputs
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  
  // Set digit pins as outputs
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);
  
  // Initially turn off all digits
  digitalWrite(DIGIT_1, LOW);
  digitalWrite(DIGIT_2, LOW);
  digitalWrite(DIGIT_3, LOW);
  digitalWrite(DIGIT_4, LOW);
  
  // Set up Timer1 for display refresh
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 500;  // Set compare match register for 2kHz refresh rate
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS11);    // 8 prescaler
  TIMSK1 |= (1 << OCIE1A);  // Enable timer compare interrupt
  interrupts();
}

void loop() {
  // Read and display temperature
  int temperature = tempSensor.readTemperature() * 100;
  displayNumber(temperature, 2);
  delay(100);  // Small delay to prevent too frequent temperature readings
}
