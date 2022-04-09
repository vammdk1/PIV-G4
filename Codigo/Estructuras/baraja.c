#include <stdio.h>
#include <string.h>
#include "carta.h"
#include "baraja.h"

void crearBaraja(Baraja* baraja, int cuantas , Carta* cartas){
    baraja->numcartas = cuantas;
    baraja->cartas = (Carta*) malloc(sizeof(Carta) * cuantas);
    for(int i = 0; i<cuantas ; i++){
        baraja->numcartas[i] = cartas[i];
    }



}
void imprimeBaraja(Baraja baraja){
    for(int i = 0 ; i < baraja.numcartas ; i++){
        imprimeCarta(baraja.cartas[i]);
    }




}

void liberaBaraja(Baraja* baraja){

    free(baraja->cartas);
    free(baraja);
}