#ifndef PIEZA_H
#define PIEZA_H

class Pieza{

private:
    int identificador;
    int coordenadas [4][2];

public:
    Pieza();
    bool moverse(int, int); //lados y abajo
    bool detectarLimiteTablero(int);
    void rotar(float); //rotar hacia izq o derecha
    void setId(int, int[2]);
    void mostrarCord();
    int getId();
    int getCord(int, int);
};

#endif
