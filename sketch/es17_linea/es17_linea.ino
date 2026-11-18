// Scheda 17 - Due sensori TCRT5000 per seguire una linea nera
// OUT del sensore sinistro sul pin 5, OUT del sensore destro sul pin 4.
// Sul bianco il modulo riceve la luce riflessa e OUT va LOW; sul nero OUT resta HIGH.

const int PIN_SX = 5;
const int PIN_DX = 4;
const int PIN_LED = 13;     // si accende quando la linea è persa

String ultimo = "";

void setup() {
  pinMode(PIN_SX, INPUT);
  pinMode(PIN_DX, INPUT);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool neroSx = (digitalRead(PIN_SX) == HIGH);
  bool neroDx = (digitalRead(PIN_DX) == HIGH);
  String azione;

  if (neroSx && neroDx) {
    azione = "DRITTO        (linea sotto entrambi)";
  } else if (neroSx) {
    azione = "GIRA A SINISTRA (la linea scappa a sinistra)";
  } else if (neroDx) {
    azione = "GIRA A DESTRA   (la linea scappa a destra)";
  } else {
    azione = "LINEA PERSA!  (fermati e cercala)";
  }
  digitalWrite(PIN_LED, !neroSx && !neroDx);

  if (azione != ultimo) {           // stampa solo quando cambia qualcosa
    Serial.print("SX=");
    Serial.print(neroSx ? "nero  " : "bianco");
    Serial.print("  DX=");
    Serial.print(neroDx ? "nero  " : "bianco");
    Serial.print("  -> ");
    Serial.println(azione);
    ultimo = azione;
  }
  delay(20);
}
