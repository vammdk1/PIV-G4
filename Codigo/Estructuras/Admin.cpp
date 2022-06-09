#include "Admin.h"

Admin::Admin() : Usuario(){

}
Admin::Admin(std::string nombre, std::string contra) : Usuario(nombre, contra){

}
Admin::~Admin(){

}

bool Admin::login(UserDatabase *udb){
    std::string temp;
    temp = udb->selectPlayer(this->contrasena.c_str(), this->nombre.c_str());
    return temp != "error" &&  temp == "1";
}
void Admin::signup(UserDatabase *udb){
    std::string admin = "1";
    udb->insertNewUser(this->nombre.c_str(), this->contrasena.c_str(), admin.c_str())
}
void Admin::execute(){
    std::cout << "EJECUTAR" << std::endl;
}