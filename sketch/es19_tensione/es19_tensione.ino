// Scheda 19 - Misurare la tensione di una batteria con il sensore 0-25 V
// S del modulo su A0, "-" del modulo su GND. La batteria va nel morsetto a vite (VCC = +, GND = -).

const int PIN_V = A0;
const float VREF = 5.0;       // misura il 5V di Arduino con il multimetro e scrivi qui il valore vero
const float RAPPORTO = 5.0;   // il modulo divide la tensione per 5 (30 kΩ + 7,5 kΩ)
const float V_VUOTA = 3.0;    // cella al litio 18650: scarica
const float V_PIENA = 4.2;    // cella al litio 18650: carica
const int PIN_LED = 13;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long somma = 0;                     // media di 20 letture: il valore "balla" meno
  for (int i = 0; i < 20; i++) {
    somma += analogRead(PIN_V);
    delay(5);
  }
  float lettura = somma / 20.0;
  float suPin = lettura * VREF / 1023.0;   // tensione che arriva su A0 (0-5 V)
  float batteria = suPin * RAPPORTO;       // tensione vera della batteria (0-25 V)

  float perc = (batteria - V_VUOTA) / (V_PIENA - V_VUOTA) * 100.0;
  perc = constrain(perc, 0, 100);

  Serial.print("Batteria: ");
  Serial.print(batteria, 2);
  Serial.print(" V   carica circa ");
  Serial.print(perc, 0);
  Serial.println(" %");

  digitalWrite(PIN_LED, batteria < 3.3 && batteria > 1.0);   // LED = "ricaricami!"
  delay(1000);
}
