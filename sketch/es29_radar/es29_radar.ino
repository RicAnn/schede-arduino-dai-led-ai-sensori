// Scheda 29 - Il radar sentinella: tre HC-SR04 su un servo fanno la guardia
// Sensori montati a mezzaluna sulla squadretta del servo, a 0, 60 e 120 gradi.
// Sensore 1: TRIG 13, ECHO 12 - Sensore 2: TRIG 11, ECHO 10 - Sensore 3: TRIG 9, ECHO 8
// Servo (segnale) sul pin 7, buzzer (+) sul pin 6, LED (S) sul pin 5.

#include <Servo.h>

const int TRIG[3] = {13, 11, 9};
const int ECHO[3] = {12, 10, 8};
const int PIN_SERVO = 7;
const int PIN_BUZZER = 6;
const int PIN_LED = 5;

const int SFASAMENTO = 60;   // gradi fra un sensore e l'altro sulla mezzaluna
const int PASSO = 5;         // il servo si sposta di 5 gradi alla volta...
const int N_POS = SFASAMENTO / PASSO + 1;   // ...da 0 a 60: 13 posizioni
const int DIST_MAX = 200;    // cm: oltre non ci interessa (e il timeout resta corto)
const int SCARTO = 20;       // cm più vicino della mappa = "c'è qualcosa"
const int CONFERME = 2;      // quante passate di fila prima di dare l'allarme

Servo servo;
int mappa[3][N_POS];         // la stanza "vuota", imparata all'accensione
byte sospetti[3][N_POS];     // quante volte di fila ogni direzione ha visto qualcosa

int misura(int s) {
  digitalWrite(TRIG[s], LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG[s], HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG[s], LOW);
  long durata = pulseIn(ECHO[s], HIGH, DIST_MAX * 58L);  // 58 us per ogni cm (andata e ritorno)
  delay(30);                     // si aspetta che l'eco si spenga prima del sensore successivo
  if (durata == 0) return DIST_MAX;
  return min((int)(durata / 58), DIST_MAX);
}

void vaiA(int pos) {
  servo.write(pos * PASSO);
  delay(80);                     // tempo per arrivare e smettere di vibrare
}

void impara() {
  Serial.println("Imparo la stanza: non passare davanti al radar...");
  for (int p = 0; p < N_POS; p++) {
    vaiA(p);
    for (int s = 0; s < 3; s++) {
      int somma = 0;
      for (int k = 0; k < 3; k++) somma += misura(s);   // media di 3 misure
      mappa[s][p] = somma / 3;
      sospetti[s][p] = 0;
    }
  }
  Serial.println("Fatto: sorveglianza attiva");
}

void allarme(int s, int p, int cm) {
  Serial.print("!!! ALLARME: oggetto a ");
  Serial.print(cm);
  Serial.print(" cm, direzione ");
  Serial.print(s * SFASAMENTO + p * PASSO);
  Serial.println(" gradi");
  for (int k = 0; k < 6; k++) {   // sirena e LED per circa 3 secondi
    digitalWrite(PIN_LED, HIGH);
    tone(PIN_BUZZER, 1800, 250);
    delay(250);
    digitalWrite(PIN_LED, LOW);
    tone(PIN_BUZZER, 1200, 250);
    delay(250);
  }
}

void controlla(int p) {
  vaiA(p);
  for (int s = 0; s < 3; s++) {
    int cm = misura(s);
    if (cm < mappa[s][p] - SCARTO) {
      sospetti[s][p]++;
      if (sospetti[s][p] >= CONFERME) {
        allarme(s, p, cm);
        sospetti[s][p] = 0;
      }
    } else {
      sospetti[s][p] = 0;
    }
  }
}

void setup() {
  for (int s = 0; s < 3; s++) {
    pinMode(TRIG[s], OUTPUT);
    pinMode(ECHO[s], INPUT);
  }
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  servo.attach(PIN_SERVO);
  delay(3000);                  // 3 secondi per allontanarsi
  impara();
}

void loop() {
  for (int p = 0; p < N_POS; p++) controlla(p);        // andata: da 0 a 60 gradi
  for (int p = N_POS - 2; p > 0; p--) controlla(p);    // ritorno: da 55 a 5 gradi
}
