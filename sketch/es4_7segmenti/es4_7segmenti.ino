// Scheda 4 - Display a 7 segmenti: contatore da 0 a 9
// Display a catodo comune. Segmenti a..g sui pin 2..8 (220 ohm ciascuno).

const int SEGMENTI[7] = {2, 3, 4, 5, 6, 7, 8};   // a, b, c, d, e, f, g

// 1 = segmento acceso. Ordine delle colonne: a b c d e f g
const byte CIFRE[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 1, 0, 1, 1}   // 9
};

void mostraCifra(int n) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(SEGMENTI[i], CIFRE[n][i] ? HIGH : LOW);
  }
}

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(SEGMENTI[i], OUTPUT);
  }
}

void loop() {
  for (int n = 0; n <= 9; n++) {
    mostraCifra(n);
    delay(1000);
  }
}
