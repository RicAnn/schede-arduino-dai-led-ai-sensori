// Scheda 21 - Sensore di polveri sottili SDS011 (PM2.5 e PM10)
// TX del sensore sul pin 10 di Arduino, 5V e GND. L'RX del sensore resta libero.
// Il sensore invia ogni secondo un messaggio di 10 byte:
// AA C0 PM25basso PM25alto PM10basso PM10alto ID1 ID2 CHECKSUM AB

#include <SoftwareSerial.h>

SoftwareSerial sensore(10, 11);   // RX = 10 (riceve dal sensore), TX = 11 (non usato)
const int PIN_LED = 13;

byte buf[10];
int pos = 0;

void setup() {
  Serial.begin(9600);
  sensore.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  Serial.println("Attendo i dati dell'SDS011...");
}

String giudizio(float pm25) {          // soglie OMS 2021 per la media giornaliera
  if (pm25 <= 15) return "buona";
  if (pm25 <= 35) return "discreta";
  if (pm25 <= 55) return "scadente";
  return "pessima";
}

void loop() {
  while (sensore.available()) {
    byte b = sensore.read();
    if (pos == 0 && b != 0xAA) continue;          // aspetta l'inizio del messaggio
    if (pos == 1 && b != 0xC0) { pos = 0; continue; }
    buf[pos++] = b;
    if (pos == 10) {
      pos = 0;
      byte somma = 0;
      for (int i = 2; i <= 7; i++) somma += buf[i];
      if (buf[9] != 0xAB || somma != buf[8]) {    // messaggio rovinato: lo scartiamo
        Serial.println("(messaggio non valido)");
        continue;
      }
      float pm25 = (buf[2] + buf[3] * 256) / 10.0;   // microgrammi per metro cubo
      float pm10 = (buf[4] + buf[5] * 256) / 10.0;
      Serial.print("PM2.5: ");
      Serial.print(pm25, 1);
      Serial.print(" ug/m3   PM10: ");
      Serial.print(pm10, 1);
      Serial.print(" ug/m3   aria ");
      Serial.println(giudizio(pm25));
      digitalWrite(PIN_LED, pm25 > 35);
    }
  }
}
