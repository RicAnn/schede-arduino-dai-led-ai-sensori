// Scheda 23 - Orologio RTC DS3231: data, ora e un timer per la lampada della serra
// SDA e SCL del modulo su SDA e SCL di Arduino, VCC su 5V, GND su GND. Libreria "RTClib" (Adafruit).
// Il LED sulla scheda (pin 13) fa da lampada: acceso dalle ORA_ON alle ORA_OFF.

#include <RTClib.h>

// #define WOKWI          // togli le due barre se usi Wokwi, che ha il modello DS1307

#ifdef WOKWI
RTC_DS1307 rtc;
#else
RTC_DS3231 rtc;
#endif

const int PIN_LAMPADA = 13;
const int ORA_ON = 7;      // la lampada si accende alle 7:00...
const int ORA_OFF = 21;    // ...e si spegne alle 21:00
const char* GIORNI[] = {"domenica", "lunedi'", "martedi'", "mercoledi'", "giovedi'", "venerdi'", "sabato"};

void dueCifre(int n) {
  if (n < 10) Serial.print('0');
  Serial.print(n);
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LAMPADA, OUTPUT);
  if (!rtc.begin()) {
    Serial.println("RTC non trovato: controlla SDA e SCL");
    while (true);
  }
#ifndef WOKWI
  if (rtc.lostPower()) {      // batteria nuova o scarica: rimettiamo l'ora
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   // data e ora della compilazione
  }
#endif
}

void loop() {
  DateTime ora = rtc.now();

  Serial.print(GIORNI[ora.dayOfTheWeek()]);
  Serial.print(' ');
  dueCifre(ora.day());   Serial.print('/');
  dueCifre(ora.month()); Serial.print('/');
  Serial.print(ora.year());
  Serial.print("  ");
  dueCifre(ora.hour());   Serial.print(':');
  dueCifre(ora.minute()); Serial.print(':');
  dueCifre(ora.second());

  bool lampada = (ora.hour() >= ORA_ON && ora.hour() < ORA_OFF);
  digitalWrite(PIN_LAMPADA, lampada);
  Serial.print(lampada ? "  lampada ACCESA" : "  lampada spenta");

#ifndef WOKWI
  Serial.print("  temp. modulo ");
  Serial.print(rtc.getTemperature(), 1);   // il DS3231 ha anche un termometro
  Serial.print(" C");
#endif
  Serial.println();
  delay(1000);
}
