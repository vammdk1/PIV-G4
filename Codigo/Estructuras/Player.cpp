#include "Player.h"

Player::Player() : Usuario(){

}
Player::Player(std::string nombre, std::string contra) : Usuario(nombre, contra){

}
Player::~Player(){

}

bool Player::login(sqlite3 *db){
    std::cout << "lLamada";
    std::string temp; 
    char* name;
    strcpy(name, this->nombre.c_str());
    std::cout << name;
    char* passw;
    strcpy(passw, this->contrasena.c_str());
    std::cout << passw;
    
    temp = selectUser(db, name, passw);
    return temp != "error" && temp == "0";
}
void Player::signup(sqlite3 *db){
   std::string player = "0";
   char* name;
   char* passw;
   char* p;
   strcpy(name, this->nombre.c_str());
   strcpy(passw, this->contrasena.c_str());
   strcpy(p, player.c_str());
   insertNewUser(db, name,passw,p);
}
void Player::execute(){
    std::cout << "EJECUTAR" << std::endl;
}