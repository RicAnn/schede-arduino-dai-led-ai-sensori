// Scheda 14 - Comandi a distanza con ricevitore IR e telecomando
// Uscita del ricevitore (OUT / DAT / S) sul pin 11, LED sulla scheda (pin 13).
// Libreria: "IRremote" (versione 4 o successiva).

#include <IRremote.hpp>

const int PIN_IR = 11;
const int PIN_LED = 13;

// Codici dei tasti: dipendono dal telecomando!
// Carica lo sketch, premi i tasti, leggi i codici sul Monitor Seriale
// e scrivili qui. Questi sono quelli del telecomando di Wokwi.
const int TASTO_1 = 48;
const int TASTO_2 = 24;
const int TASTO_3 = 122;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  IrReceiver.begin(PIN_IR);        // avvia il ricevitore
  Serial.println("Premi un tasto del telecomando");
}

void lampeggia(int volte) {
  for (int i = 0; i < volte; i++) {
    digitalWrite(PIN_LED, HIGH);
    delay(150);
    digitalWrite(PIN_LED, LOW);
    delay(150);
  }
}

void loop() {
  if (IrReceiver.decode()) {                        // è arrivato un segnale?
    int codice = IrReceiver.decodedIRData.command;
    Serial.print("Codice ricevuto: ");
    Serial.println(codice);

    if (codice == TASTO_1) digitalWrite(PIN_LED, HIGH);   // 1 = accendi
    if (codice == TASTO_2) digitalWrite(PIN_LED, LOW);    // 2 = spegni
    if (codice == TASTO_3) lampeggia(3);                  // 3 = lampeggia

    IrReceiver.resume();                            // pronto per il prossimo tasto
  }
}
