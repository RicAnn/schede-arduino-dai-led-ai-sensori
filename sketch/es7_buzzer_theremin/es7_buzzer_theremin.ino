// Scheda 7 - Buzzer passivo: tieni premuto il pulsante e suona,
// il potenziometro decide la nota (un piccolo "theremin").
// Pulsante sul pin 2, cursore del potenziometro su A0, buzzer (+) sul pin 8.

const int PIN_PULSANTE = 2;
const int PIN_POT = A0;
const int PIN_BUZZER = 8;

void setup() {
  pinMode(PIN_PULSANTE, INPUT_PULLUP);   // premuto = LOW
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {
  if (digitalRead(PIN_PULSANTE) == LOW) {
    int valore = analogRead(PIN_POT);                // da 0 a 1023
    int frequenza = map(valore, 0, 1023, 200, 2000); // da 200 Hz a 2000 Hz
    tone(PIN_BUZZER, frequenza);                     // suona la nota
  } else {
    noTone(PIN_BUZZER);                              // silenzio
  }
}
