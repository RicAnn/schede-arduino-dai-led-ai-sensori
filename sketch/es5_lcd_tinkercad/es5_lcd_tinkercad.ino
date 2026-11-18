// Scheda 5 - Display LCD 16x2 I2C (versione per Tinkercad)
// Componente "LCD 16 x 2 (I2C)": GND, VCC=5V, SDA, SCL.

#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);   // indirizzo 0 = impostazione predefinita di Tinkercad

void setup() {
  lcd.begin(16, 2);              // 16 colonne, 2 righe
  lcd.setBacklight(1);           // accende la retroilluminazione
  lcd.print("Ciao Robotica!");   // prima riga
}

void loop() {
  lcd.setCursor(0, 1);           // colonna 0, riga 1 (la seconda)
  lcd.print("Secondi: ");
  lcd.print(millis() / 1000);    // secondi dall'accensione
  delay(200);
}
