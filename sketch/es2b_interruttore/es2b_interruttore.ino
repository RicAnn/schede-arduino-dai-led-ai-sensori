// Scheda 2 (versione B) - Il pulsante diventa un interruttore
// Ogni pressione cambia lo stato del LED: acceso -> spento -> acceso...

const int PIN_PULSANTE = 2;
const int PIN_LED = 13;

bool ledAcceso = false;        // stato attuale del LED
int statoPrecedente = HIGH;    // lettura del pulsante al giro precedente

void setup() {
  pinMode(PIN_PULSANTE, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  int stato = digitalRead(PIN_PULSANTE);

  // Agiamo solo nell'istante in cui il pulsante passa da HIGH a LOW
  if (statoPrecedente == HIGH && stato == LOW) {
    ledAcceso = !ledAcceso;                  // inverte lo stato
    digitalWrite(PIN_LED, ledAcceso ? HIGH : LOW);
    delay(50);                               // antirimbalzo (debounce)
  }
  statoPrecedente = stato;
}
