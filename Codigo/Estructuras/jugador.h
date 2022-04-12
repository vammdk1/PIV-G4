#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "carta.h"
#include "baraja.h"
#include "jugador.h"

typedef struct{

int numero;
char* nombre;
Baraja cartasnegras;

}Jugador;

void crearJugador(Jugador* jug , int numero, char* nombre , Baraja baraja);


#endif /* JUGADOR_H_ */