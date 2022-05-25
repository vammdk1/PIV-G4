#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carta.h"
#include "baraja.h"

void crearBaraja(Baraja* baraja, int cuantas , Carta* cartas){
    baraja->numcartas = cuantas;
    baraja->cartas = (Carta*) malloc(sizeof(Carta) * cuantas);
    for(int i = 0; i<cuantas ; i++){
        baraja->cartas[i] = cartas[i];
    }
}
void imprimirBaraja(Baraja baraja){
    for(int i = 0 ; i < baraja.numcartas ; i++){
        imprimirCarta(baraja.cartas[i]);
    }
}

void liberaBaraja(Baraja* baraja){

    free(baraja->cartas);
    free(baraja);
}

Carta seleccionarCarta(Baraja* baraja, unsigned int pos){
    return baraja->cartas[pos % baraja->numcartas];
}

/**
void cambiarCarta(Baraja* baraja, unsigned int pos, Carta* nuevaCarta){
    free(baraja->cartas[pos]);
    baraja->cartas[pos] = (Carta*) malloc(sizeof(Carta));
    *(baraja->cartas[pos]) = &nuevaCarta;
}**/