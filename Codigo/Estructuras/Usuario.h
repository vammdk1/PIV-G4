#ifndef _USUARIO_H_
#define _USUARIO_H_
#include <string>
extern "C"{
    #include "../DataBase/DataBase.h"
}
class Usuario
{
protected:
    std::string nombre;
    std::string contrasena;
public:
    Usuario();
    Usuario(std::string nombre, std::string contra);
    virtual ~Usuario();

    void setNombre(std::string nombre);
    void setContra(std::string contra);
    std::string getNombre();
    std::string getContra();

    virtual bool login(sqlite3 *db) = 0;
    virtual void signup(sqlite3 *db) = 0;

    virtual void execute() = 0;
};

#endif
