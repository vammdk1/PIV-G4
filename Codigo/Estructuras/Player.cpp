#include "Player.h"

Player::Player() : Usuario(){

}
Player::Player(std::string nombre, std::string contra) : Usuario(nombre, contra){

}
Player::~Player(){

}

bool Player::login(UserDatabase *udb){
    std::string temp;
    temp = udb->selectPlayer(this->contrasena.c_str(), this->nombre.c_str());
    return temp != "error" && temp == "0";
}
void Player::signup(UserDatabase *udb){
    std::string player = "0";
    udb->insertNewUser(this->nombre.c_str(), this->contrasena.c_str(), player.c_str())
}
void Player::execute(){
    std::cout << "EJECUTAR" << std::endl;
}