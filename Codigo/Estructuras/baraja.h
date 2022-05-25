#ifndef BARAJA_H_
#define BARAJA_H_
#include "carta.h"


typedef struct{

Carta* cartas;
int numcartas;

}Baraja;

void crearBaraja(Baraja* baraja, int cuantas , Carta* cartas);
void imprimirBaraja(Baraja baraja);
void liberaBaraja(Baraja* baraja);
Carta seleccionarCarta(Baraja* baraja, unsigned int pos);
//void cambiarCarta(Baraja* baraja, unsigned int pos, Carta* nuevaCarta);

#endif