// Scheda 11 - Sensore di parcheggio con l'HC-SR04
// TRIG sul pin 12, ECHO sul pin 11, buzzer (+) sul pin 8.

const int PIN_TRIG = 12;
const int PIN_ECHO = 11;
const int PIN_BUZZER = 8;

void setup() {
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  Serial.begin(9600);
}

float misuraDistanza() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);       // impulso di 10 microsecondi:
  delayMicroseconds(10);              // il sensore emette 8 "click" a 40 kHz
  digitalWrite(PIN_TRIG, LOW);

  long durata = pulseIn(PIN_ECHO, HIGH, 30000);  // tempo di andata e ritorno (us)
  if (durata == 0) return 999;                   // nessun eco: niente davanti
  return durata * 0.0343 / 2;                    // velocità del suono: 0,0343 cm/us
}

void loop() {
  float cm = misuraDistanza();
  Serial.print("Distanza: ");
  Serial.print(cm, 1);
  Serial.println(" cm");

  if (cm < 10) {
    tone(PIN_BUZZER, 1500);           // vicinissimo: suono continuo
    delay(100);
  } else if (cm < 60) {
    tone(PIN_BUZZER, 1500, 80);       // bip...
    delay(cm * 10);                   // ...sempre più fitti man mano che ti avvicini
  } else {
    noTone(PIN_BUZZER);
    delay(100);
  }
}
