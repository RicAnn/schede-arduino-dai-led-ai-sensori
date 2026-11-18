// Rover.h - una piccola libreria per guidare un rover con due motori e il driver L298N
// Riccardo Annolfi - Schede di laboratorio Arduino
#ifndef ROVER_H
#define ROVER_H

#include <Arduino.h>

class Rover {
  public:
    // pin del motore sinistro (ENA, IN1, IN2) e del motore destro (ENB, IN3, IN4)
    Rover(int ena, int in1, int in2, int enb, int in3, int in4);

    void begin();                          // da chiamare in setup()

    // comandi di guida: velocità da 0 a 255
    void avanti(int vel);
    void indietro(int vel);
    void sinistra(int vel);                // gira sul posto verso sinistra
    void destra(int vel);                  // gira sul posto verso destra
    void curva(int velSx, int velDx);      // ogni motore da -255 a +255
    void stop();                           // rallenta fino a fermarsi (con la rampa)
    void freno();                          // si ferma subito

    // regolazioni
    void rampa(int unitaAlSecondo);        // accelerazione: 0 = immediata, 300 = da 0 a 255 in 0,85 s
    void correzione(int percSx, int percDx);  // es. (100, 92) se il rover tende a curvare a destra

    // da chiamare il più spesso possibile nel loop()
    void aggiorna();
    // come delay(), ma intanto aggiorna la rampa
    void attendi(unsigned long ms);
    bool fermo();

  private:
    int _ena, _in1, _in2, _enb, _in3, _in4;
    int _obSx = 0, _obDx = 0;              // velocità desiderate
    float _sx = 0, _dx = 0;                // velocità attuali
    int _rampa = 300;
    int _corrSx = 100, _corrDx = 100;
    unsigned long _ultimo = 0;
    void _motore(int en, int a, int b, int vel);
};

#endif
