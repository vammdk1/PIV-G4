#include "Admin.h"

Admin::Admin() : Usuario(){

}
Admin::Admin(std::string nombre, std::string contra) : Usuario(nombre, contra){

}
Admin::~Admin(){

}

bool Admin::login(sqlite3 *db){
    std::string temp;
    char* name;
    char* passw;
    strcpy(name, this->nombre.c_str());
    strcpy(passw, this->contrasena.c_str());
    temp = selectUser(db, name, passw);
    return temp != "error" &&  temp == "1";
}
void Admin::signup(sqlite3 *db){
   std::string player = "1";
   char* name;
   char* passw;
   char* p;
   strcpy(name, this->nombre.c_str());
   strcpy(passw, this->contrasena.c_str());
   strcpy(p, player.c_str());
   insertNewUser(db, name,passw,p);
}
void Admin::execute(){
    std::cout << "EJECUTAR" << std::endl;
}