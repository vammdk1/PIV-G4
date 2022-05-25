#ifndef JUGADOR_H_
#define JUGADOR_H_

extern "C"{
    #include "baraja.h"
    #include "carta.h"
    #include <string.h>
}


class Jugador{
    private:
        Baraja baraja;
        char* nombre;
        int puntos;
        bool rey;
    public:
        Jugador();
        Jugador(Carta* cartas, char* nombre);
        ~Jugador();
        bool esRey();
        void cambiarRey();
        int getPuntos();
        char* getNombre();
        void sumarPuntos(int puntos);
        Carta seleccionarCarta(unsigned int pos);
        void cambiarCarta(Carta* nuevaCarta, int pos);

};


#endif 