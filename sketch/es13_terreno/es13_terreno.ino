// Scheda 13 - Quando annaffiare? Sensore di umidità del terreno
// SIG su A0, alimentazione del sensore dal pin 7, LED sulla scheda (pin 13).

const int PIN_SENSORE = A0;
const int PIN_ALIM = 7;       // accendiamo il sensore solo quando serve
const int PIN_LED = 13;

// Taratura: valore letto con il sensore all'aria (secco) e in un bicchiere d'acqua (bagnato).
// Con il sensore capacitivo i valori sono invertiti (secco alto, bagnato basso):
// basta scambiare i due numeri.
const int SECCO = 0;
const int BAGNATO = 876;

void setup() {
  pinMode(PIN_ALIM, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
}

int leggiUmidita() {
  digitalWrite(PIN_ALIM, HIGH);   // accendi il sensore
  delay(10);
  int valore = analogRead(PIN_SENSORE);
  digitalWrite(PIN_ALIM, LOW);    // spegnilo: le punte si corrodono molto meno
  return valore;
}

void loop() {
  int valore = leggiUmidita();
  int percento = constrain(map(valore, SECCO, BAGNATO, 0, 100), 0, 100);

  Serial.print("Valore: ");
  Serial.print(valore);
  Serial.print("   Umidita del terreno: ");
  Serial.print(percento);
  Serial.print(" %   ");

  if (percento < 30) {
    Serial.println("SECCO: annaffia!");
    digitalWrite(PIN_LED, HIGH);
  } else if (percento < 70) {
    Serial.println("ok");
    digitalWrite(PIN_LED, LOW);
  } else {
    Serial.println("troppa acqua");
    digitalWrite(PIN_LED, LOW);
  }
  delay(1000);
}
