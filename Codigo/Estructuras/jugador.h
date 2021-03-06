#ifndef JUGADOR_H_
#define JUGADOR_H_

extern "C"{
    
    #include "carta.h"
   
}
#include <string.h>
#include <stdlib.h>
using namespace std;



class Jugador{
    private:
        Carta* arrayCartas;
        char* nombre;
        int puntos;
        bool rey;
        int id;
    public:
        Jugador();
        Jugador(char* nombre);
        Jugador(const Jugador& jugador);
        ~Jugador();
        bool esRey();
        void cambiarRey();
        int getPuntos();
        char* getNombre();
        void setNombre(char* nombre);
        void setPuntos(int puntos);
        void sumarPuntos(int puntos);
        Carta seleccionarCarta(unsigned int pos);
        void cambiarCarta(Carta* nuevaCarta, int pos);
        void setID(int id);
        int getID();

};


#endif 