// Scheda 20 - Bilancia con cella di carico e amplificatore HX711
// DT dell'HX711 sul pin 3, SCK sul pin 2. Libreria "HX711" di Bogdan Necula (bogde).
// Dal Monitor Seriale: invia "t" per azzerare (tara), "r" per vedere il valore grezzo.

#include "HX711.h"

const int PIN_DT = 3;
const int PIN_SCK = 2;
float FATTORE = 0.42;    // unità grezze per grammo: 0.42 va bene per Wokwi, sulla cella vera va tarato

HX711 bilancia;

void setup() {
  Serial.begin(9600);
  bilancia.begin(PIN_DT, PIN_SCK);
  Serial.println("Togli tutto dal piatto: azzero...");
  delay(1000);
  bilancia.set_scale(FATTORE);
  bilancia.tare();               // il peso attuale (piatto vuoto) diventa lo zero
  Serial.println("Pronta! Appoggia un oggetto.");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 't') {
      bilancia.tare();
      Serial.println("Tara fatta");
    }
    if (c == 'r') {
      Serial.print("Valore grezzo (senza tara): ");
      Serial.println(bilancia.get_value(10));
    }
  }

  float grammi = bilancia.get_units(5);   // media di 5 letture, già divisa per FATTORE
  if (abs(grammi) < 1) grammi = 0;        // niente "-0.3 g" a piatto vuoto
  Serial.print("Peso: ");
  Serial.print(grammi, 0);
  Serial.println(" g");
  delay(500);
}
