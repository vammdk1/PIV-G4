#ifndef _ADMIN_H_
#define _ADMIN_H_
#include <string>
#include <iostream>
#include "Usuario.h"
extern "C"{
    #include "../DataBase/DataBase.h"
    #include <string.h>
}
class Admin : public Usuario
{
private:
    
public:
    Admin();
    Admin(std::string nombre, std::string contra);
    virtual ~Admin();

    virtual bool login(sqlite3 *db);
    virtual void signup(sqlite3 *db);

    virtual void execute();
};
#endif