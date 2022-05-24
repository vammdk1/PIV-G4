#include "Jugador.h"

Jugador::Jugador(Carta* cartas, char* nombre){

    crearBaraja(baraja, 7, cartas);
    this->nombre = new char[20];
    strcpy(this->nombre, nombre);
    puntos = 0;

}

Jugador::~Jugador(){
    delete(nombre);
    liberaBaraja();
}

bool Jugador::Jugador(){
    return rey;

}

void Jugador::cambiarRey(){
    rey = !rey;
}

int Jugador::getPuntos(){
    return puntos;
}

void Jugador::sumarPuntos(int puntos){
    this->puntos += puntos;
}

Carta Jugador::seleccionarCarta(unsigned int pos){
    return seleccionarCarta(this->baraja, pos);
}

void Jugador::cambiarCarta(Carta* nuevaCarta, int pos){
    cambiarCarta(this->baraja, pos, nuevaCarta);
}