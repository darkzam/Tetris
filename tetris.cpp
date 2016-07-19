#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <ncurses.h>
#include <ctime>
#include <random>
#include <math.h>
#include <vector>
#include <algorithm>
#include "tetris.h"
#define PI 3.14159265

 Tetris::Tetris(){
    generarMapaVacio();

}

void Tetris::generarMapaVacio(){
    for(int i=0 ; i<20 ; i++){
      for(int j=0; j<10; j++){
        mapa [i][j] = 0;
        }}
}

void Tetris::mostrarEstado(){

      for(int i=0 ; i<20 ; i++){
        for(int j=0; j<10; j++){
             int imprimir = mapa [i][j];

              for(int k=0 ; k<4; k++){
                int fila = pz1.getCord(k,0);
                int columna = pz1.getCord(k,1);
                    if( fila == i && columna == j){
                       imprimir= pz1.getId();
                    }
                }
              move(i,j);
              init_pair( imprimir, imprimir , imprimir); 

              attron(COLOR_PAIR(imprimir));
              printw("%d", imprimir);
              attroff(COLOR_PAIR(imprimir));
              refresh();  
        }
      }
}

void Tetris::generarPieza(){
    //pone la pieza en el mapa , en las coordenadas de inicio
 //generar un numero entre 1 y 7
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_int_distribution<> dist(1, 7);
    int cord[2]={0,4};
    pz1.setId(dist(e2),cord);

}

void Tetris::ubicarPieza(int idocero){

     for(int i=0 ; i<4 ; i++){

        mapa[pz1.getCord(i,0)][pz1.getCord(i,1)] = idocero;

      }

}

void Tetris::iniciar(){

    Tetris::generarPieza();
    
    std::chrono::time_point<std::chrono::system_clock> start, finish;

    initscr();
    nodelay(stdscr, true);
    keypad(stdscr,true);
    noecho();
    curs_set(0);
    start_color();

    start = std::chrono::system_clock::now();
    Tetris::mostrarEstado();

   while(true){

    Tetris::eventosTeclado();
    finish = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = finish-start;

    if( elapsed_seconds.count() >= 1.0){
        start = finish;
        if( !Tetris::detectarColision(1,0)){
     
            pz1.moverse(1,0);
      
        }else{

            ubicarPieza(pz1.getId());
            //chequear por lineas destruidas
            Tetris::puntaje();
            Tetris::generarPieza();
        }
    }
    Tetris::mostrarEstado();

    //esperar un delay bajito para lectura del input
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

   }

   endwin();
}

bool Tetris::detectarColision(int direccion, int componente){

    for(int i=0 ; i<4 ; i++){

     int fila = pz1.getCord(i,0);
     int columna = pz1.getCord(i,1);

    if(componente==0){

    if(fila>=19 && direccion==1){

        return true;
    }
    if(fila<=0 && direccion==-1){
  
        return true;
    }
    if(mapa[fila+direccion][columna]!=0){

            return true;
        }
    }

    if(componente==1){

        if(columna>=9 && direccion==1){
            return true;
        }
        if(columna<=0 && direccion==-1){
            return true;
        }

        if(mapa[fila][columna+direccion]!= 0){

            return true;
        }
    }

      }
      return false;
}

bool Tetris::colisionGiro(float angulo){

     int tmp [4][2];

     for(int i=0; i<4 ; i++){

         tmp[i][0] = pz1.getCord(i,0);
         tmp[i][1] = pz1.getCord(i,1);
     }

     int xc = tmp[1][0];
     int yc = tmp[1][1];

     for(int i=0; i<4 ; i++){
    // 1. calculo todas las coordenadas de giro angulo 90
            //coordenadas X's
        int x = tmp[i][0];
        int y = tmp[i][1];

        tmp[i][0] = xc+(x-xc)*static_cast<int>(cos(angulo*PI/180))-(y-yc)*static_cast<int>(sin(angulo*PI/180));
        tmp[i][1] = yc+(x-xc)*static_cast<int>(sin(angulo*PI/180))+(y-yc)*static_cast<int>(cos(angulo*PI/180));

        if( tmp[i][0]<0 || tmp[i][1]<0){

            return true;

        }

        if (tmp[i][0]>19 || tmp[i][1]>9 ){

            return true;
        }

        if(mapa[tmp[i][0]][tmp[i][1]] != 0){

            return true;
        }
     }

    return false;
}

void Tetris::puntaje(){

    std::vector< int > arr;

    //buscar una fila o filas llenas
    int filaAnterior=-1;

    for(int i=0; i<4 ; i++){

        int fila = pz1.getCord(i,0);

        if( fila == filaAnterior){
            continue;
        }

        for(int j=0; j<10 ; j++){

            if(mapa[fila][j]==0){

            break;

            }

            if(j==9){

                arr.push_back(fila);
            }

        }

        filaAnterior = fila;
    }

    if(!arr.empty()){


        for(int i=0 ; i< arr.size() ; i++){

            for(int j=0; j<10 ; j++){

                mapa[arr[i]][j] = 0;
      
            }

        }
        // ordenar el vector de menor a mayor
        std::sort(arr.begin(), arr.end(), std::less<int>());

         for(int k=0 ; k< arr.size() ; k++){

            for(int i=arr[k] ; i>-1 ; i--){


                for(int j=0; j<10 ; j++){

                    if(mapa[i][j]!=0 && mapa[i+1][j]==0){

                        mapa[i+1][j]= mapa[i][j];
                        mapa[i][j] = 0;
                    }
                }

            }
         }

    }
}



void Tetris::eventosTeclado(){
        //detect key
        int tmp=getch();
        switch(tmp)
        {
                case KEY_LEFT:
                        if(!Tetris::detectarColision(-1,1))
                                pz1.moverse(-1,1);
                                Tetris::mostrarEstado();
                        break;
                case KEY_RIGHT:
                        if(!Tetris::detectarColision(1,1))
                                pz1.moverse(1,1);
                                Tetris::mostrarEstado();
                        break;
                case KEY_DOWN:
                        if(!Tetris::detectarColision(1,0))
                                pz1.moverse(1,0);
                                Tetris::mostrarEstado();
                        break;
                case KEY_UP:
                        if(!colisionGiro(90.0) && pz1.getId()!=1){
                            pz1.rotar(90.0);
                            Tetris::mostrarEstado();
                            }
                        break;

        }

}
