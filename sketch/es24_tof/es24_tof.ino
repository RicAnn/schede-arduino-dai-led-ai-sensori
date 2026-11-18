// Scheda 24 - Sensore di distanza laser a tempo di volo (ToF) VL53L0X
// VIN su 5V, GND su GND, SCL su SCL, SDA su SDA. Libreria "Adafruit_VL53L0X".
// Il LED sulla scheda (pin 13) si accende quando un oggetto è più vicino di 10 cm.

#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X tof;
const int PIN_LED = 13;
const int VICINO_MM = 100;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  if (!tof.begin()) {
    Serial.println("VL53L0X non trovato: controlla i collegamenti");
    while (true);
  }
  Serial.println("ToF pronto");
}

void loop() {
  VL53L0X_RangingMeasurementData_t misura;
  tof.rangingTest(&misura, false);

  if (misura.RangeStatus != 4) {          // 4 = fuori portata
    int mm = misura.RangeMilliMeter;
    Serial.print("Distanza: ");
    Serial.print(mm);
    Serial.print(" mm  ");
    for (int i = 0; i < mm / 25 && i < 40; i++) Serial.print('=');   // una barra
    Serial.println('|');
    digitalWrite(PIN_LED, mm < VICINO_MM);
  } else {
    Serial.println("fuori portata (oltre circa 1,2 m)");
    digitalWrite(PIN_LED, LOW);
  }
  delay(100);
}
