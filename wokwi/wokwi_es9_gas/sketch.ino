// Scheda 9 - Allarme gas con il modulo MQ-2
// AO del modulo su A0, DO sul pin 7, buzzer (+) sul pin 3, LED sulla scheda (pin 13).

const int PIN_GAS_A = A0;   // uscita analogica: quanto gas c'è
const int PIN_GAS_D = 7;    // uscita digitale: LOW quando si supera la soglia del trimmer blu
const int PIN_BUZZER = 3;
const int PIN_LED = 13;     // il LED "L" saldato su Arduino
const int SOGLIA = 400;     // da tarare: guarda i valori in aria pulita e scegli un po' più in alto

void setup() {
  pinMode(PIN_GAS_D, INPUT);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Preriscaldamento del sensore...");
  delay(20000);             // il sensore va scaldato: aspettiamo 20 secondi
  Serial.println("Pronto!");
}

void loop() {
  int gas = analogRead(PIN_GAS_A);
  bool sogliaModulo = (digitalRead(PIN_GAS_D) == LOW);

  Serial.print("Gas: ");
  Serial.print(gas);
  Serial.print("   Soglia del modulo superata: ");
  Serial.println(sogliaModulo ? "SI" : "no");

  if (gas > SOGLIA) {        // ALLARME: bip intermittente e LED
    digitalWrite(PIN_LED, HIGH);
    tone(PIN_BUZZER, 2000, 150);
    delay(150);
    digitalWrite(PIN_LED, LOW);
    delay(150);
  } else {
    digitalWrite(PIN_LED, LOW);
    delay(300);
  }
}
