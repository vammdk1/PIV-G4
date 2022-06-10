#include <iostream>
#include <string>

#include "Admin.h"
#include "Player.h"
#include "Usuario.h"

extern "C"{
    #include "../DataBase/DataBase.h"
}

int main()
{
    sqlite3 *db;
    std::string ruta = "../Archivos/database.db";
    sqlite3_open(ruta.c_str() , &db);
    std::cout << "Bienvenido a el launcher oficial de CMD contra la humanidad" << std::endl;
    std::string respuesta = "";
    while (respuesta != "5")
    {
        std::cout << "Que desea? 1-Log In User, 2-Sign Up User, 3- Log In Admin, 4- Sign Up Admin, 5- Salir" << std::endl;
        std::cin >> respuesta;
        if(respuesta == "1"){

            std::string nombre;
            std::string contra;
            std::cout << "Cual es tu nombre?" << std::endl;
            std::cin >> nombre;
            std::cout << "Contrasena?" << std::endl;
            std::cin >> contra;
            Player *p = new Player(nombre, contra);
            
            bool loginOk = p->login(db);
            if(loginOk){
                std::cout << "Login adecuado, Ejecutar Servidor? [S/N]" << std::endl;
                std::cout << "NOTA: El cliente debe ser ejecutado manualmente" << std::endl;
                std::cin >> respuesta;
                if(respuesta == "S"){
                    sqlite3_close(db);
                    p->execute();
                    sqlite3_open(ruta.c_str() , &db);
                }
            } else {
                std::cout << "Login inadecuado, por favor asegurese de que sus credenciales son correctas y que tiene una cuenta en CMD contra la humanidad" << std::endl;
            }
            delete p;

        }else if (respuesta == "2")
        {
            std::string nombre;
            std::string contra;
            std::cout << "Cual es tu nombre?" << std::endl;
            std::cin >> nombre;
            std::cout << "Contrasena?" << std::endl;
            std::cin >> contra;
            Player *p = new Player(nombre, contra);
            p->signup(db);
            delete p;
        }else if (respuesta == "3")
        {
            std::string nombre;
            std::string contra;
            std::cout << "Cual es tu nombre?" << std::endl;
            std::cin >> nombre;
            std::cout << "Contrasena?" << std::endl;
            std::cin >> contra;
            Admin *p = new Admin(nombre, contra);
            bool loginOk = p->login(db);
            if(loginOk){
                
                std::cout << "Login adecuado, Ejecutar Gestion de base de datos? [S/N]" << std::endl;
                std::cin >> respuesta;
                if(respuesta == "S"){
                    sqlite3_close(db);
                    p->execute();
                    sqlite3_open(ruta.c_str() , &db);
                }
            }else{
                std::cout << "Login inadecuado, por favor asegurese de que sus credenciales son correctas y que tiene una cuenta en CMD contra la humanidad" << std::endl;
            }
            delete p;
        }else if (respuesta == "4")
        {
            std::string nombre;
            std::string contra;
            std::cout << "Cual es tu nombre?" << std::endl;
            std::cin >> nombre;
            std::cout << "Contrasena?" << std::endl;
            std::cin >> contra;
            Admin *p = new Admin(nombre, contra);
            p->signup(db);
            delete p;
        }else if (respuesta == "7")
        {
            system("color 01");
        } else if(respuesta != "5"){
            std::cout << "Respuesta no valida" << std::endl;
        }

    
    }
    
    
    return 0;
}

