// Scheda 15 - Livella elettronica con l'MPU6050 (accelerometro + giroscopio)
// Collegamento I2C: VCC a 5V, GND a GND, SCL su SCL (A5), SDA su SDA (A4).
// Libreria: "Adafruit MPU6050" (accetta anche le dipendenze proposte).

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
const int PIN_LED = 13;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  if (!mpu.begin()) {                  // indirizzo I2C 0x68
    Serial.println("MPU6050 non trovato: controlla SDA e SCL");
    while (true) delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t acc, gyro, temp;
  mpu.getEvent(&acc, &gyro, &temp);

  float ax = acc.acceleration.x;       // in m/s^2: da fermo misura la gravità (9,8)
  float ay = acc.acceleration.y;
  float az = acc.acceleration.z;

  // angoli di inclinazione calcolati dalla direzione della gravità
  float rollio = atan2(ay, az) * 180.0 / PI;
  float beccheggio = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

  // formato "nome:valore" -> leggibile anche dal Plotter Seriale
  Serial.print("Rollio:");
  Serial.print(rollio, 1);
  Serial.print(" Beccheggio:");
  Serial.print(beccheggio, 1);
  Serial.print(" Rotazione_Z:");
  Serial.println(gyro.gyro.z * 180.0 / PI, 1);   // gradi al secondo

  // in bolla: LED acceso se entrambi gli angoli sono entro 2 gradi
  bool inBolla = abs(rollio) < 2 && abs(beccheggio) < 2;
  digitalWrite(PIN_LED, inBolla ? HIGH : LOW);
  delay(100);
}
