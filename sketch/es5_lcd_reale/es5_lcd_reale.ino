// Scheda 5 - Display LCD 16x2 I2C (versione per la scheda reale)
// Libreria da installare: "LiquidCrystal I2C" (Frank de Brabander).

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // se lo schermo resta vuoto prova 0x3F

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("Ciao Robotica!");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print("Secondi: ");
  lcd.print(millis() / 1000);
  delay(200);
}
