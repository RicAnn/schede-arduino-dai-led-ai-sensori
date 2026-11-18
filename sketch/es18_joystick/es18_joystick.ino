// Scheda 18 - Joystick analogico
// VRx su A0, VRy su A1, SW (pulsante) su A2 usato come pin digitale, LED sulla scheda (pin 13).

const int PIN_X = A0;
const int PIN_Y = A1;
const int PIN_SW = A2;     // anche i pin analogici funzionano come digitali
const int PIN_LED = 13;
const int ZONA_MORTA = 120;   // intorno al centro (512) non consideriamo il movimento

void setup() {
  pinMode(PIN_SW, INPUT_PULLUP);   // il pulsante del joystick chiude verso GND
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(PIN_X);       // 0 ... 512 (centro) ... 1023
  int y = analogRead(PIN_Y);
  bool premuto = (digitalRead(PIN_SW) == LOW);

  String direzione = "";
  if (y > 512 + ZONA_MORTA) direzione += "SU ";
  if (y < 512 - ZONA_MORTA) direzione += "GIU' ";
  if (x > 512 + ZONA_MORTA) direzione += "SINISTRA";
  if (x < 512 - ZONA_MORTA) direzione += "DESTRA";
  if (direzione == "") direzione = "centro";

  // trasformiamo la posizione in una "velocità" da -100 a +100
  int velX = map(x, 0, 1023, 100, -100);
  int velY = map(y, 0, 1023, -100, 100);

  Serial.print("X=");
  Serial.print(x);
  Serial.print("  Y=");
  Serial.print(y);
  Serial.print("  vel(");
  Serial.print(velX);
  Serial.print(", ");
  Serial.print(velY);
  Serial.print(")  ");
  Serial.print(direzione);
  Serial.println(premuto ? "  [PREMUTO]" : "");

  digitalWrite(PIN_LED, premuto);
  delay(150);
}
