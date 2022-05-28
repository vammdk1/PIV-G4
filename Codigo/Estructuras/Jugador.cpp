#include "Jugador.h"
#include <iostream>

Jugador::Jugador(char* nombre){

    this->arrayCartas = new Carta[7];
     char* temp = new char[20];
    strcpy(temp, "Texto de ejemplo");
    for(int i = 0; i < 7; i++){
        arrayCartas[i].negra = 0;
        
        setTexto(&(arrayCartas[i]), temp);
        
        arrayCartas[i].id = 0;
        
    }
    delete[] temp;
    this->nombre = new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);
    puntos = 0;
    rey = false;

}
Jugador::Jugador(){
    
    this->arrayCartas = new Carta[7];
    
    char* temp = new char[20];
    strcpy(temp, "Texto de ejemplo");
    for(int i = 0; i < 7; i++){
        arrayCartas[i].negra = 0;
        
        setTexto(&(arrayCartas[i]), temp);
       
        arrayCartas[i].id = 0;
        
    }
    delete[] temp;
    
    this->nombre = new char[7];
    strcpy(this->nombre, "NoName");
    
    puntos = 0;
    
    rey = false;
    
}

Jugador::Jugador(const Jugador& jugador){
    this->nombre = new char[strlen(jugador.nombre)+1];
   
    for(int i = 0; i < 7; i++){
        arrayCartas[i].negra = 0;
        
        setTexto(&(arrayCartas[i]), jugador.arrayCartas[i].texto);
       
        arrayCartas[i].id = 0;
        
    }
    
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
    for(int i = 0; i < 7;i++){
       freeTexto(&arrayCartas[i]);
    }
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
void Jugador::setPuntos(int puntos){
    this->puntos = puntos;
}

void Jugador::sumarPuntos(int puntos){
    this->puntos += puntos;
}

Carta Jugador::seleccionarCarta(unsigned int pos){
    return arrayCartas[pos];
}

void Jugador::cambiarCarta(Carta* nuevaCarta, int pos){
    arrayCartas[pos].id = nuevaCarta->id;
    arrayCartas[pos].negra = nuevaCarta->negra;
    freeTexto(&(this->arrayCartas[pos]));
    setTexto(&(arrayCartas[pos]), nuevaCarta->texto);
    delete nuevaCarta;
}

void Jugador::setID(int id){
    this->id = id;
}
int Jugador::getID(){
    return id;
}