// Scheda 7 (versione B) - Una pressione del pulsante suona "Fra Martino".
// Il potenziometro regola la velocità della melodia.

const int PIN_PULSANTE = 2;
const int PIN_POT = A0;
const int PIN_BUZZER = 8;

// frequenze delle note (Hz)
const int DO = 262, RE = 294, MI = 330, FA = 349, SOL = 392;

const int NOTE[]   = {DO, RE, MI, DO,  DO, RE, MI, DO,  MI, FA, SOL,  MI, FA, SOL};
const int DURATE[] = { 1,  1,  1,  1,   1,  1,  1,  1,   1,  1,  2,    1,  1,  2};  // 1 = un battito
const int N = sizeof(NOTE) / sizeof(NOTE[0]);           // quante note ci sono

void setup() {
  pinMode(PIN_PULSANTE, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(PIN_PULSANTE) == LOW) {
    for (int i = 0; i < N; i++) {
      int battito = map(analogRead(PIN_POT), 0, 1023, 150, 600);  // ms per battito
      tone(PIN_BUZZER, NOTE[i]);
      delay(battito * DURATE[i] * 9 / 10);   // la nota suona per il 90% del tempo...
      noTone(PIN_BUZZER);
      delay(battito * DURATE[i] / 10);       // ...poi una breve pausa separa le note
    }
  }
}
