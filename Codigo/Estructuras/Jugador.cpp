#include "Jugador.h"
#include <iostream>

Jugador::Jugador(char* nombre){

    this->arrayCartas = new Carta[7];
    this->nombre = new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);
    puntos = 0;
    bool rey = false;

}
Jugador::Jugador(){
    
    this->arrayCartas = new Carta[7];
    
    this->nombre = new char[7];
    strcpy(this->nombre, "NoName");
    
    puntos = 0;
    
    rey = false;
    
}

Jugador::Jugador(const Jugador& jugador){
    this->nombre = new char[strlen(jugador.nombre)+1];
    strcpy(this->nombre, jugador.nombre);
    this->puntos = jugador.puntos;
    bool rey = false;
    this->arrayCartas = new Carta[7];
    for(int i = 0; i<7; i++){
        this->arrayCartas[i] = jugador.arrayCartas[i];
    }
   
}

Jugador::~Jugador(){
    delete[] nombre;
    delete[] arrayCartas;
    
}

bool Jugador::esRey(){
    return rey;

}

void Jugador::cambiarRey(){
    rey = !rey;
}

int Jugador::getPuntos(){
    return puntos;
}
char* Jugador::getNombre(){
    return nombre;
}
void Jugador::setNombre(char* nombre){
    strcpy(this->nombre, nombre);
}

void Jugador::sumarPuntos(int puntos){
    this->puntos += puntos;
}

Carta Jugador::seleccionarCarta(unsigned int pos){
    return arrayCartas[pos];
}

void Jugador::cambiarCarta(Carta* nuevaCarta, int pos){
    arrayCartas[pos].id = nuevaCarta->id;
    strcpy(arrayCartas[pos].texto, nuevaCarta->texto);
}