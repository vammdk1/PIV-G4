#include "Admin.h"

Admin::Admin() : Usuario(){

}
Admin::Admin(std::string nombre, std::string contra) : Usuario(nombre, contra){

}
Admin::~Admin(){

}

bool Admin::login(sqlite3 *db){
    std::string temp;
    char* name = new char[strlen(this->nombre.c_str())+1];
    char* passw = new char[strlen(this->contrasena.c_str())+1];
    strcpy(name, this->nombre.c_str());
    strcpy(passw, this->contrasena.c_str());
    temp = selectUser(db, passw, name);
    
    delete[] name;
    delete[] passw;
    return temp != "error" &&  temp == "1";
}
void Admin::signup(sqlite3 *db){
   std::string player = "1";
   char* name = new char[strlen(this->nombre.c_str())+1];
   char* passw = new char[strlen(this->contrasena.c_str())+1];
   char* p = new char[2];
   strcpy(name, this->nombre.c_str());
   strcpy(passw, this->contrasena.c_str());
   strcpy(p, player.c_str());
   insertNewUser(db, name,passw,p);
   delete[] name;
   delete[] passw;
   delete[] p;
}
void Admin::execute(){
    std::cout << "EJECUTANDO" << std::endl;
    system("GestorDB.exe");
}