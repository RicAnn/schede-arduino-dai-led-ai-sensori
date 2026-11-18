// Scheda 8 - Luce notturna automatica con fotoresistenza (LDR)
// Partitore: 5V -> LDR -> A0 -> 10 kohm -> GND. LED (con 220 ohm) sul pin PWM 9.

const int PIN_LDR = A0;
const int PIN_LED = 9;
const int BUIO = 300;     // sotto questo valore consideriamo che sia buio (da tarare)

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int luce = analogRead(PIN_LDR);    // più luce = numero più alto
  Serial.print("Luce: ");
  Serial.println(luce);

  if (luce < BUIO) {
    // più è buio, più il LED è luminoso
    int luminosita = map(luce, 0, BUIO, 255, 20);
    analogWrite(PIN_LED, luminosita);
  } else {
    analogWrite(PIN_LED, 0);          // c'è luce: LED spento
  }
  delay(100);
}
