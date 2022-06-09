#ifndef _DATABASE_H_
#define _DATABASE_H_
extern "C"{
    #include "sqlite3.h"
    #include <string.h>
}
#include <iostream>

class UserDatabase
{
private:
    sqlite3 *db;
public:
    UserDatabase(std::string ruta);
    ~UserDatabase();

    
     int createDataBase();
     int createTables();
     int deleteTables();

     int insertNewUser(char* nombre, char* contra, char* admin);


     char* selectPlayer( char* contra, char* nombre);

     

};






#endif