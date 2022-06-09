#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include <iostream>
#include "Usuario.h"
#include "../DataBase/UserDatabase.h"
class Player : public Usuario
{
private:
    
public:
    Player();
    Player(std::string nombre, std::string contra);
    virtual ~Player();

    virtual bool login(UserDatabase *udb);
    virtual void signup(UserDatabase *udb);

    virtual void execute();
};
#endif