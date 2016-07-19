#ifndef TETRIS_H
#define TETRIS_H
#include "pieza.h"

class Tetris{
private:
    int mapa [20][10];
    int puntos;
    Pieza pz1;

public:
    Tetris();
    void generarMapaVacio();
    void mostrarEstado();
    void iniciar();
    void generarPieza();
    void ubicarPieza(int);
    void eventosTeclado();
    void puntaje();
    bool detectarColision(int,int);
    bool colisionGiro(float);
};

#endif
