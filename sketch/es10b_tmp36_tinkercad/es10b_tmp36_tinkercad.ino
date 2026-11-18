// Scheda 10 (versione Tinkercad) - Termometro con il sensore TMP36
// Piedino centrale del TMP36 su A0, gli altri due a 5V e GND.

const int PIN_TMP = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int lettura = analogRead(PIN_TMP);
  float volt = lettura * 5.0 / 1024.0;      // da numero a tensione
  float gradi = (volt - 0.5) * 100.0;       // TMP36: 10 mV per grado, 0,5 V a 0 gradi

  Serial.print("Temperatura: ");
  Serial.print(gradi, 1);
  Serial.println(" C");
  delay(500);
}
