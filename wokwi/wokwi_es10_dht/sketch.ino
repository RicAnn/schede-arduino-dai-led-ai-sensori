// Scheda 10 - Temperatura e umidità con DHT11 / DHT22
// Pin dati del sensore sul pin 2.
// Librerie: "DHT sensor library" e "Adafruit Unified Sensor" (entrambe di Adafruit).

#include <DHT.h>

#define PIN_DHT 2
#define TIPO_DHT DHT22     // scrivi DHT11 se usi il sensore azzurro

DHT dht(PIN_DHT, TIPO_DHT);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Stazione meteo pronta");
}

void loop() {
  delay(2000);                                // il DHT si legge al massimo ogni 1-2 secondi

  float umidita = dht.readHumidity();         // in percentuale
  float temperatura = dht.readTemperature();  // in gradi Celsius

  if (isnan(umidita) || isnan(temperatura)) { // isnan = "non è un numero"
    Serial.println("Errore di lettura: controlla i collegamenti");
    return;
  }

  float percepita = dht.computeHeatIndex(temperatura, umidita, false);

  Serial.print("Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.print(" C   Umidita: ");
  Serial.print(umidita, 0);
  Serial.print(" %   Percepita: ");
  Serial.print(percepita, 1);
  Serial.println(" C");
}
