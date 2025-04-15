int dataPin = 4;
int latchPin = 5;
int clockPin = 6;

int CA_1 = 12;
int CA_2 = 11;
int CA_3 = 10;
int CA_4 = 9;

int count = 0;

int CAS[4] = {12, 11, 10, 9};

byte dec_digits[] = {0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000011,0b11111000,0b10000000,0b10011000 };

void setup() {
  //ustawienie pinów jako wyjść (output) w celu sterowania rejestrem przesuwnym
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(CA_1, OUTPUT);
  pinMode(CA_2, OUTPUT);
  pinMode(CA_3, OUTPUT);
  pinMode(CA_4, OUTPUT);

  digitalWrite(CA_1, HIGH);
  digitalWrite(CA_2, HIGH);
  digitalWrite(CA_3, HIGH);
  digitalWrite(CA_4, HIGH);
}

void loop() {
  for (int numberToDisplay = 0; numberToDisplay < 10; numberToDisplay++) {
    // take the latchPin low so
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[numberToDisplay]);
    digitalWrite(CAS[count], LOW); //turn on the relevent digit
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    count++; //count up the digit
    if (count == 4) { // keep the count between 0-3
      count = 0;
    }
    // pause before next value:
    delay(300);
  }
}