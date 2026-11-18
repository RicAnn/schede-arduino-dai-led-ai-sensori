// Scheda 2 - Pulsante e LED
// Pulsante tra il pin 2 e GND, LED (con 220 ohm) sul pin 13.

const int PIN_PULSANTE = 2;
const int PIN_LED = 13;

void setup() {
  pinMode(PIN_PULSANTE, INPUT_PULLUP); // attiva la resistenza di pull-up interna
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  // Con il pull-up il pin vale HIGH a riposo e LOW quando premi
  if (digitalRead(PIN_PULSANTE) == LOW) {
    digitalWrite(PIN_LED, HIGH);       // premuto: LED acceso
  } else {
    digitalWrite(PIN_LED, LOW);        // rilasciato: LED spento
  }
}
