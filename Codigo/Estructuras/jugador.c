#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "carta.h"
#include "baraja.h"
#include "jugador.h"

void crearJugador(Jugador* jug , int numero, char* nombre , Baraja baraja){
    jug->cartasnegras = baraja;
    jug->nombre = nombre;
    jug->numero = numero;


}