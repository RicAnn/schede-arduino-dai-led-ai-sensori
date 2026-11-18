// Rover.cpp - il codice della libreria
#include "Rover.h"

Rover::Rover(int ena, int in1, int in2, int enb, int in3, int in4)
  : _ena(ena), _in1(in1), _in2(in2), _enb(enb), _in3(in3), _in4(in4) {}

void Rover::begin() {
  int pin[] = {_ena, _in1, _in2, _enb, _in3, _in4};
  for (int i = 0; i < 6; i++) pinMode(pin[i], OUTPUT);
  freno();
  _ultimo = millis();
}

void Rover::avanti(int vel)   { curva(vel, vel); }
void Rover::indietro(int vel) { curva(-vel, -vel); }
void Rover::sinistra(int vel) { curva(-vel, vel); }    // ruota sinistra indietro, destra avanti
void Rover::destra(int vel)   { curva(vel, -vel); }
void Rover::stop()            { curva(0, 0); }

void Rover::curva(int velSx, int velDx) {
  _obSx = constrain(velSx, -255, 255);
  _obDx = constrain(velDx, -255, 255);
  if (_rampa == 0) {                       // senza rampa: subito alla velocità richiesta
    _sx = _obSx;
    _dx = _obDx;
  }
  aggiorna();
}

void Rover::freno() {
  _obSx = _obDx = 0;
  _sx = _dx = 0;
  digitalWrite(_in1, HIGH); digitalWrite(_in2, HIGH); analogWrite(_ena, 255);
  digitalWrite(_in3, HIGH); digitalWrite(_in4, HIGH); analogWrite(_enb, 255);
}

void Rover::rampa(int unitaAlSecondo) { _rampa = max(unitaAlSecondo, 0); }

void Rover::correzione(int percSx, int percDx) {
  _corrSx = constrain(percSx, 0, 100);
  _corrDx = constrain(percDx, 0, 100);
}

// porta la velocità attuale verso quella desiderata, un pezzetto alla volta
static float avvicina(float attuale, int obiettivo, float passo) {
  if (attuale < obiettivo) return min(attuale + passo, (float)obiettivo);
  if (attuale > obiettivo) return max(attuale - passo, (float)obiettivo);
  return attuale;
}

void Rover::aggiorna() {
  unsigned long ora = millis();
  float dt = (ora - _ultimo) / 1000.0;     // secondi passati dall'ultima volta
  _ultimo = ora;
  if (_rampa > 0) {
    float passo = _rampa * dt;
    _sx = avvicina(_sx, _obSx, passo);
    _dx = avvicina(_dx, _obDx, passo);
  }
  _motore(_ena, _in1, _in2, (int)_sx * _corrSx / 100);
  _motore(_enb, _in3, _in4, (int)_dx * _corrDx / 100);
}

void Rover::attendi(unsigned long ms) {
  unsigned long inizio = millis();
  while (millis() - inizio < ms) {
    aggiorna();
    delay(5);
  }
}

bool Rover::fermo() { return _sx == 0 && _dx == 0; }

void Rover::_motore(int en, int a, int b, int vel) {
  digitalWrite(a, vel > 0 ? HIGH : LOW);
  digitalWrite(b, vel < 0 ? HIGH : LOW);
  analogWrite(en, abs(vel));
}
