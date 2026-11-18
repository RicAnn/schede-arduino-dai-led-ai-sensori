// Scheda 12 - Antifurto con il sensore di movimento PIR
// OUT del PIR sul pin 12, buzzer (+) sul pin 8, LED sulla scheda (pin 13).

const int PIN_PIR = 12;
const int PIN_BUZZER = 8;
const int PIN_LED = 13;

int intrusioni = 0;
bool primaFermo = true;     // al giro precedente non c'era movimento?

void setup() {
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Attendi 30 secondi: il PIR si sta stabilizzando...");
  delay(30000);
  Serial.println("Antifurto ATTIVO");
}

void loop() {
  bool movimento = (digitalRead(PIN_PIR) == HIGH);

  if (movimento) {
    if (primaFermo) {                 // il movimento è appena iniziato
      intrusioni++;
      Serial.print("Movimento rilevato! Intrusioni: ");
      Serial.println(intrusioni);
    }
    digitalWrite(PIN_LED, HIGH);      // sirena: due toni alternati
    tone(PIN_BUZZER, 880);
    delay(200);
    tone(PIN_BUZZER, 660);
    delay(200);
  } else {
    digitalWrite(PIN_LED, LOW);
    noTone(PIN_BUZZER);
  }
  primaFermo = !movimento;
}
