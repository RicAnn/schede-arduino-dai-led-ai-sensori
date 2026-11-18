// Scheda 3 - Potenziometro che regola la luminosità di un LED
// Cursore del potenziometro su A0, LED (con 220 ohm) sul pin PWM 9.

const int PIN_POT = A0;
const int PIN_LED = 9;           // il simbolo ~ indica un pin PWM

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);            // apre il Monitor Seriale
}

void loop() {
  int valore = analogRead(PIN_POT);               // da 0 a 1023
  int luminosita = map(valore, 0, 1023, 0, 255);  // da 0 a 255
  analogWrite(PIN_LED, luminosita);               // PWM sul LED

  Serial.print("Potenziometro: ");
  Serial.print(valore);
  Serial.print("   Luminosita: ");
  Serial.println(luminosita);
  delay(50);
}
