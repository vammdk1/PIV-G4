#ifndef _ADMIN_H_
#define _ADMIN_H_
#include <string>
#include <iostream>
#include "Usuario.h"
#include "../DataBase/UserDatabase.h"
class Admin : public Usuario
{
private:
    
public:
    Admin();
    Admin(std::string nombre, std::string contra);
    virtual ~Admin();

    virtual bool login(UserDatabase *udb);
    virtual void signup(UserDatabase *udb);

    virtual void execute();
};
#endif