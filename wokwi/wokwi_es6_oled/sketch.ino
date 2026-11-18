// Scheda 6 - Display OLED 128x64 I2C (SSD1306)
// Librerie: "Adafruit SSD1306" e "Adafruit GFX Library".

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);   // larghezza, altezza, bus I2C

int x = 10;     // posizione orizzontale della pallina
int dx = 3;     // velocità (pixel per fotogramma)

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {   // indirizzo tipico 0x3C
    for (;;);                                         // display non trovato
  }
}

void loop() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("ROBOTICA");

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print("Ciao dall'OLED!");

  display.drawRect(0, 34, 128, 12, SSD1306_WHITE);                 // cornice
  display.fillRect(2, 36, (millis() / 50) % 124, 8, SSD1306_WHITE); // barra che cresce

  display.fillCircle(x, 56, 6, SSD1306_WHITE);   // pallina
  display.display();                             // mostra tutto sullo schermo

  x += dx;
  if (x < 6 || x > 121) dx = -dx;                // rimbalza sui bordi
  delay(30);
}
