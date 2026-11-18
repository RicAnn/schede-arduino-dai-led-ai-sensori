// Scheda 27 - Il rover: guida con la libreria Rover (due motori e driver L298N)
// Motore sinistro: ENA pin 10, IN1 pin 9, IN2 pin 8. Motore destro: ENB pin 3, IN3 pin 7, IN4 pin 4.
// I file Rover.h e Rover.cpp devono stare nella stessa cartella dello sketch.

#include "Rover.h"

Rover rover(10, 9, 8, 3, 7, 4);

void setup() {
  Serial.begin(9600);
  rover.begin();
  rover.rampa(300);            // accelera da 0 a 255 in circa 0,85 secondi
  rover.correzione(100, 100);  // se va storto, abbassa la percentuale del motore più veloce
  Serial.println("Il rover parte tra 3 secondi: tienilo sollevato per la prima prova!");
  delay(3000);
}

void loop() {
  Serial.println("Avanti");
  rover.avanti(200);
  rover.attendi(2000);

  Serial.println("Stop dolce");
  rover.stop();
  rover.attendi(1000);

  Serial.println("Gira a sinistra");
  rover.sinistra(160);
  rover.attendi(700);

  Serial.println("Gira a destra");
  rover.destra(160);
  rover.attendi(700);

  Serial.println("Indietro piano");
  rover.indietro(120);
  rover.attendi(1500);

  Serial.println("Curva larga (sinistro piano, destro veloce)");
  rover.curva(100, 220);
  rover.attendi(1500);

  Serial.println("Freno!");
  rover.freno();
  delay(3000);
}
