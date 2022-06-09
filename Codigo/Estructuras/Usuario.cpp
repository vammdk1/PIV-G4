#include "Usuario.h"
Usuario::Usuario(){
    this->nombre = "";
    this->contrasena = "";
}
Usuario::Usuario(std::string nombre, std::string contra){
    this->nombre = nombre;
    this->contrasena = contra;
}
Usuario::~Usuario(){

}

void Usuario::setNombre(std::string nombre){
    this->nombre = nombre;
}
void Usuario::setContra(std::string contra){
    this->contrasena = contra;
}
std::string Usuario::getNombre(){
    return this->nombre;
}
std::string Usuario::getContra(){
    return this->contrasena;
}



