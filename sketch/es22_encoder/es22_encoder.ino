// Scheda 22 - Encoder rotativo KY-040: una manopola "infinita"
// CLK sul pin 4, DT sul pin 3, SW sul pin 2. Premi la manopola per tornare a 0.

const int PIN_CLK = 4;
const int PIN_DT = 3;
const int PIN_SW = 2;

int livello = 0;              // da 0 a 20, come il volume di una radio
int clkPrima;

void setup() {
  pinMode(PIN_CLK, INPUT_PULLUP);
  pinMode(PIN_DT, INPUT_PULLUP);
  pinMode(PIN_SW, INPUT_PULLUP);
  Serial.begin(9600);
  clkPrima = digitalRead(PIN_CLK);
  mostra();
}

void mostra() {
  Serial.print("Livello ");
  if (livello < 10) Serial.print(" ");
  Serial.print(livello);
  Serial.print("  [");
  for (int i = 0; i < 20; i++) Serial.print(i < livello ? '#' : '.');
  Serial.println("]");
}

void loop() {
  int clk = digitalRead(PIN_CLK);
  if (clk != clkPrima && clk == LOW) {      // è iniziato uno scatto
    if (digitalRead(PIN_DT) == HIGH) {
      livello++;                            // senso orario
    } else {
      livello--;                            // senso antiorario
    }
    livello = constrain(livello, 0, 20);
    mostra();
  }
  clkPrima = clk;

  if (digitalRead(PIN_SW) == LOW) {
    livello = 0;
    mostra();
    while (digitalRead(PIN_SW) == LOW) delay(10);   // aspetta il rilascio
  }
}
