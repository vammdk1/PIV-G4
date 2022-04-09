#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "baraja.h"

typedef struct{

int numero;
char* nombre;
Baraja cartasnegras;

}Jugador;

void crearJugador(Jugador* jug , char* nombre , Baraja baraja);


#endif /* JUGADOR_H_ */