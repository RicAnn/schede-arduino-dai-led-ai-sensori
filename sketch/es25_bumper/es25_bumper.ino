// Scheda 25 - Paraurti (bumper) con due microswitch
// Microswitch sinistro: NO sul pin 3, COM su GND. Microswitch destro: NO sul pin 2, COM su GND.
// Il LED sulla scheda (pin 13) lampeggia a ogni urto. Il programma dice che cosa dovrebbe fare il rover.

const int PIN_SX = 3;
const int PIN_DX = 2;
const int PIN_LED = 13;

int urti = 0;

void setup() {
  pinMode(PIN_SX, INPUT_PULLUP);    // premuto = LOW, come il pulsante della Scheda 2
  pinMode(PIN_DX, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Rover in marcia...");
}

void urto(const char* lato, const char* manovra) {
  urti++;
  for (int i = 0; i < 3; i++) {     // tre lampi veloci
    digitalWrite(PIN_LED, HIGH); delay(60);
    digitalWrite(PIN_LED, LOW);  delay(60);
  }
  Serial.print("URTO ");
  Serial.print(lato);
  Serial.print(" (n. ");
  Serial.print(urti);
  Serial.print(") -> indietro per 0,5 s, poi ");
  Serial.println(manovra);
  delay(500);                        // qui il rover andrebbe indietro...
  delay(400);                        // ...e qui girerebbe
  Serial.println("Rover in marcia...");
}

void loop() {
  bool sx = (digitalRead(PIN_SX) == LOW);
  bool dx = (digitalRead(PIN_DX) == LOW);

  if (sx && dx) {
    urto("FRONTALE", "mezzo giro");
  } else if (sx) {
    urto("a SINISTRA", "gira a destra");
  } else if (dx) {
    urto("a DESTRA", "gira a sinistra");
  }
  delay(10);
}
