// Scheda 1 - Il primo LED: Blink
// Il LED (con la sua resistenza da 220 ohm) è collegato al pin 13.

const int PIN_LED = 13;        // pin a cui è collegato il LED

void setup() {
  pinMode(PIN_LED, OUTPUT);    // il pin 13 diventa un'uscita
}

void loop() {
  digitalWrite(PIN_LED, HIGH); // 5 V sul pin: il LED si accende
  delay(1000);                 // aspetta 1000 ms = 1 secondo
  digitalWrite(PIN_LED, LOW);  // 0 V sul pin: il LED si spegne
  delay(1000);                 // aspetta ancora 1 secondo
}
