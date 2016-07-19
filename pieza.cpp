#include <iostream>
#include "pieza.h"
#include <math.h>
#define PI 3.14159265

//inicializa una pieza con -1 de id o sea ningun valor
Pieza::Pieza(): identificador(-1){

}

bool Pieza::moverse(int direccion , int componente){

   /* if( Pieza::detectarLimiteTablero(componente)){
        return false;
    }*/

    for(int i=0; i<4 ; i++){
     coordenadas [i][componente] += direccion;
    }
    //Pieza::mostrarCord();
        return true;
}

bool Pieza::detectarLimiteTablero( int componente){

     for(int i=0; i<4 ; i++){
        if(componente==0 && coordenadas[i][componente]>=19){

            return true;
        }
        if(componente==1 && coordenadas[i][componente]>=9){

            return true;
        }
    }
    return false;
}


void Pieza::rotar(float angulo){
//hacia izq o derech
    int xc = coordenadas[1][0];
    int yc = coordenadas[1][1];

    for(int i=0; i<4 ; i++){
    //coordenadas X's
    int x = coordenadas[i][0];
    int y = coordenadas[i][1];

    coordenadas[i][0]= xc+(x-xc)*static_cast<int>(cos(angulo*PI/180))-(y-yc)*static_cast<int>(sin(angulo*PI/180));
    coordenadas[i][1]= yc+(x-xc)*static_cast<int>(sin(angulo*PI/180))+(y-yc)*static_cast<int>(cos(angulo*PI/180));

    }

}

int Pieza::getId(){

    return identificador;
}

int Pieza::getCord(int fila, int columna){

    return coordenadas[fila][columna];

}

void Pieza::setId(int id , int coord[2]){
// crea la pieza con un id que es el tipo de ficha
// y una coordenada X,Y donde comenzar a generar las demas coordenadas dependiento del tipo de ficha
        identificador = id;
        switch(id)
        {
                case 1:

                    coordenadas[0][0] = coord[0];
                    coordenadas[0][1] = coord[1];
                    coordenadas[1][0] = coord[0]+1;
                    coordenadas[1][1] = coord[1];
                    coordenadas[2][0] = coord[0];
                    coordenadas[2][1] = coord[1]+1;
                    coordenadas[3][0] = coord[0]+1;
                    coordenadas[3][1] = coord[1]+1;
                        break;
                case 2:

                    coordenadas[0][0] = coord[0];
                    coordenadas[0][1] = coord[1];
                    coordenadas[1][0] = coord[0];
                    coordenadas[1][1] = coord[1]+1;
                    coordenadas[2][0] = coord[0];
                    coordenadas[2][1] = coord[1]+2;
                    coordenadas[3][0] = coord[0];
                    coordenadas[3][1] = coord[1]+3;
                        break;
                case 3:

                    coordenadas[0][0] = coord[0];
                    coordenadas[0][1] = coord[1];
                    coordenadas[1][0] = coord[0];
                    coordenadas[1][1] = coord[1]+1;
                    coordenadas[2][0] = coord[0];
                    coordenadas[2][1] = coord[1]+2;
                    coordenadas[3][0] = coord[0]+1;
                    coordenadas[3][1] = coord[1]+1;
                        break;
                case 4:

                    coordenadas[0][0] = coord[0];
                    coordenadas[0][1] = coord[1];
                    coordenadas[1][0] = coord[0];
                    coordenadas[1][1] = coord[1]+1;
                    coordenadas[2][0] = coord[0];
                    coordenadas[2][1] = coord[1]+2;
                    coordenadas[3][0] = coord[0]+1;
                    coordenadas[3][1] = coord[1];
                        break;
                 case 5:

                    coordenadas[0][0] = coord[0];
                    coordenadas[0][1] = coord[1];
                    coordenadas[1][0] = coord[0];
                    coordenadas[1][1] = coord[1]+1;
                    coordenadas[2][0] = coord[0];
                    coordenadas[2][1] = coord[1]+2;
                    coordenadas[3][0] = coord[0]+1;
                    coordenadas[3][1] = coord[1]+2;
                        break;
                 case 6:

                    coordenadas[0][0] = coord[0];
                    coordenadas[0][1] = coord[1]+1;
                    coordenadas[1][0] = coord[0];
                    coordenadas[1][1] = coord[1]+2;
                    coordenadas[2][0] = coord[0]+1;
                    coordenadas[2][1] = coord[1];
                    coordenadas[3][0] = coord[0]+1;
                    coordenadas[3][1] = coord[1]+1;
                        break;
                  case 7:

                    coordenadas[0][0] = coord[0];
                    coordenadas[0][1] = coord[1];
                    coordenadas[1][0] = coord[0];
                    coordenadas[1][1] = coord[1]+1;
                    coordenadas[2][0] = coord[0]+1;
                    coordenadas[2][1] = coord[1]+1;
                    coordenadas[3][0] = coord[0]+1;
                    coordenadas[3][1] = coord[1]+2;
                        break;

        }

}

void Pieza::mostrarCord(){

      for(int i=0 ; i<4 ; i++){
        for(int j=0; j<2; j++){

         std::cout << coordenadas[i][j]<<'\n';
        }
      }
}


