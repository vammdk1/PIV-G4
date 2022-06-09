#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include <iostream>
#include "Usuario.h"
extern "C"{
    #include "../DataBase/DataBase.h"
    #include <string.h>
}
class Player : public Usuario
{
private:
    
public:
    Player();
    Player(std::string nombre, std::string contra);
    virtual ~Player();

    virtual bool login(sqlite3 *db);
    virtual void signup(sqlite3 *db);

    virtual void execute();
};
#endif