// Scheda 26 - Un motore DC con il driver L298N
// ENA sul pin 10 (PWM), IN1 sul pin 9, IN2 sul pin 8. Togli il ponticello ENA sul driver!
// Comandi dal Monitor Seriale: a = avanti, i = indietro, s = stop, f = freno, + e - = velocità

const int ENA = 10;   // velocità (PWM)
const int IN1 = 9;    // verso
const int IN2 = 8;

int velocita = 150;   // da 0 a 255
int verso = 0;        // 1 = avanti, -1 = indietro, 0 = fermo

void motore(int vel) {          // vel da -255 (indietro) a +255 (avanti)
  if (vel > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (vel < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else {
    digitalWrite(IN1, LOW);      // IN1 = IN2: il motore si ferma per inerzia
    digitalWrite(IN2, LOW);
  }
  analogWrite(ENA, abs(vel));
}

void freno() {                   // IN1 = IN2 = HIGH con ENA al massimo: frenata decisa
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 255);
  verso = 0;
}

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  motore(0);
  Serial.begin(9600);
  Serial.println("Comandi: a = avanti, i = indietro, s = stop, f = freno, + / - = velocita'");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'a') verso = 1;
    if (c == 'i') verso = -1;
    if (c == 's') verso = 0;
    if (c == '+') velocita = min(velocita + 25, 255);
    if (c == '-') velocita = max(velocita - 25, 0);
    if (c == 'f') {
      freno();
      Serial.println("FRENO");
      return;
    }
    if (c == '\n' || c == '\r') return;     // ignora gli "a capo"
    motore(verso * velocita);
    Serial.print("verso ");
    Serial.print(verso);
    Serial.print("   velocita' ");
    Serial.print(velocita);
    Serial.print(" su 255 (");
    Serial.print(velocita * 100 / 255);
    Serial.println(" %)");
  }
}
