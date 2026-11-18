// Scheda 30 - La serra automatica: annaffia da sola quando la terra è secca
// Terreno: SIG su A0, VCC sul pin 7. DHT22: DATA sul pin 2. Relè: IN sul pin 8.
// La pompa NON si collega ad Arduino: ha il suo portabatterie e passa dal contatto del relè.

#include <DHT.h>

const int PIN_TERRENO = A0;
const int PIN_ALIM_TERRENO = 7;   // il sensore si accende solo per la misura (Scheda 13)
const int PIN_DHT = 2;
const int PIN_RELE = 8;
const int PIN_LED = 13;           // acceso mentre la pompa lavora, lampeggia se c'è un problema

// Molti moduli relè si attivano con LOW: se il tuo scatta al contrario, scambia HIGH e LOW qui.
const int RELE_ACCESO = HIGH;
const int RELE_SPENTO = LOW;

// Taratura del sensore del terreno (Scheda 13): valore all'aria e valore in acqua.
const int SECCO = 0;
const int BAGNATO = 876;

const int SOGLIA_SECCO = 35;           // sotto questa percentuale si annaffia
const int SOGLIA_OK = 50;              // sopra questa la terra è di nuovo umida
const unsigned long DURATA_POMPA = 3000;   // ms di acqua per ogni annaffiatura
const unsigned long ATTESA = 60000;        // ms per lasciare che l'acqua scenda nella terra
const int MAX_ANNAFFIATURE = 5;        // dopo 5 tentativi senza risultato: serbatoio vuoto?

DHT dht(PIN_DHT, DHT22);
unsigned long ultimaAnnaffiatura = 0;
unsigned long ultimaStampa = 0;
int tentativi = 0;
bool allarme = false;

void setup() {
  pinMode(PIN_ALIM_TERRENO, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_RELE, RELE_SPENTO);   // prima lo stato, poi l'uscita: la pompa non parte all'accensione
  pinMode(PIN_RELE, OUTPUT);
  dht.begin();
  Serial.begin(9600);
  Serial.println("Serra automatica pronta");
  ultimaAnnaffiatura = millis() - ATTESA;   // al primo giro si può annaffiare subito
}

int umiditaTerreno() {
  digitalWrite(PIN_ALIM_TERRENO, HIGH);
  delay(10);
  int valore = analogRead(PIN_TERRENO);
  digitalWrite(PIN_ALIM_TERRENO, LOW);
  return constrain(map(valore, SECCO, BAGNATO, 0, 100), 0, 100);
}

void annaffia() {
  tentativi++;
  Serial.print(">>> Annaffio (tentativo ");
  Serial.print(tentativi);
  Serial.println(")");
  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_RELE, RELE_ACCESO);    // il relè chiude il contatto: la pompa parte
  delay(DURATA_POMPA);                    // pochi secondi: qui fermarsi va bene
  digitalWrite(PIN_RELE, RELE_SPENTO);
  digitalWrite(PIN_LED, LOW);
  ultimaAnnaffiatura = millis();
}

void loop() {
  int terreno = umiditaTerreno();

  // ogni 2 secondi: stampa i valori (il DHT22 non si legge più spesso)
  if (millis() - ultimaStampa >= 2000) {
    ultimaStampa = millis();
    float temperatura = dht.readTemperature();
    float umiditaAria = dht.readHumidity();
    Serial.print("Terreno: ");
    Serial.print(terreno);
    Serial.print(" %   Aria: ");
    if (isnan(temperatura) || isnan(umiditaAria)) {
      Serial.print("errore DHT");
    } else {
      Serial.print(temperatura, 1);
      Serial.print(" C, ");
      Serial.print(umiditaAria, 0);
      Serial.print(" %");
      if (temperatura > 30) Serial.print("   fa caldo: apri la serra!");
    }
    Serial.println();
  }

  if (terreno >= SOGLIA_OK) {   // la terra è umida: tutto a posto, si azzera il contatore
    tentativi = 0;
    allarme = false;
  }

  if (allarme) {                // troppi tentativi a vuoto: pompa ferma, LED che lampeggia
    digitalWrite(PIN_LED, (millis() / 250) % 2);
    return;
  }

  // terra secca e passata l'attesa dall'ultima annaffiatura
  if (terreno < SOGLIA_SECCO && millis() - ultimaAnnaffiatura >= ATTESA) {
    if (tentativi >= MAX_ANNAFFIATURE) {
      allarme = true;
      Serial.println("!!! La terra resta secca: controlla il serbatoio e il tubicino");
    } else {
      annaffia();
    }
  }
}
