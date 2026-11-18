// Scheda 16 - Lampada touch con il sensore TTP223
// SIG del sensore sul pin 2, LED sulla scheda (pin 13).
// Un tocco breve accende o spegne, un tocco lungo (oltre 1 secondo) fa lampeggiare.

const int PIN_TOUCH = 2;
const int PIN_LED = 13;

bool acceso = false;
bool lampeggia = false;
bool primaToccato = false;
unsigned long inizioTocco = 0;

void setup() {
  pinMode(PIN_TOUCH, INPUT);        // il modulo ha già la sua uscita: niente pull-up
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool toccato = (digitalRead(PIN_TOUCH) == HIGH);   // TTP223: toccato = HIGH

  if (toccato && !primaToccato) {          // il dito è appena arrivato
    inizioTocco = millis();
  }
  if (!toccato && primaToccato) {          // il dito si è appena staccato
    unsigned long durata = millis() - inizioTocco;
    if (durata > 1000) {
      lampeggia = !lampeggia;              // tocco lungo
      Serial.println("Tocco lungo: modalita' lampeggio");
    } else {
      acceso = !acceso;                    // tocco breve
      lampeggia = false;
      Serial.println(acceso ? "Luce ACCESA" : "Luce SPENTA");
    }
  }
  primaToccato = toccato;

  if (lampeggia) {
    digitalWrite(PIN_LED, (millis() / 250) % 2);
  } else {
    digitalWrite(PIN_LED, acceso);
  }
}
