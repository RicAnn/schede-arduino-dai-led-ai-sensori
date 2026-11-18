// Scheda 28 - Il servomotore: girare di un angolo preciso
// Servo: filo arancione (segnale) sul pin 9, rosso a 5V, marrone a GND.
// Potenziometro: piedino centrale su A0, gli altri due a 5V e GND.

#include <Servo.h>

const int PIN_SERVO = 9;
const int PIN_POT = A0;

Servo servo;

void setup() {
  servo.attach(PIN_SERVO);   // da qui in poi la libreria manda un impulso ogni 20 ms
  Serial.begin(9600);
}

void loop() {
  int valore = analogRead(PIN_POT);           // da 0 a 1023
  int angolo = map(valore, 0, 1023, 0, 180);  // da 0 a 180 gradi
  servo.write(angolo);                        // il servo si porta all'angolo e ci resta

  Serial.print("Potenziometro: ");
  Serial.print(valore);
  Serial.print("   Angolo: ");
  Serial.println(angolo);
  delay(20);                                  // un nuovo angolo ogni 20 ms basta e avanza
}
