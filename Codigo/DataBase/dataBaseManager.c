#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include "CreateDataBase.h"

int main(int argc, char const *argv[])
{
    //Hacer un menu todo wapo para poder modificar, crear y tal

    //Pruebas
    sqlite3 *db;
    sqlite3_open("../Archivos/database.db", &db);
    createDataBase(db);
    sqlite3_close(db);
    return 0;
}
