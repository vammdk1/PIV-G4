#include "jugador.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int main(int argc, char const *argv[])
{
    //Pasos para meter cartas en un jugador
    Jugador* j = new Jugador();
   
    Carta* cc = (Carta*) malloc(sizeof(Carta));
    char* palabra = new char[5];
    strcpy(palabra, "holi");
   
    setTexto(cc, palabra);
   
    cc->id = 1; // la id
  
    cc->negra = 1; // si es negra
  
    j->cambiarCarta(cc, 1);

    cout << j->seleccionarCarta(1).texto << endl;
    free(cc);
    delete[] palabra;
    return 0;
}
