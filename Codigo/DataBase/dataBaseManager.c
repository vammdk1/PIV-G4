#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DataBase.h"

int main(int argc, char const *argv[])
{
    //Hacer un menu todo wapo para poder modificar, crear y tal

    //Pruebas
    sqlite3 *db;
    sqlite3_open("../Archivos/database.db", &db);
    
   // createDataBase(db);
    //createTables(db);
    //En el menu, se leera por teclado los datos a meter, la ID sera generada Auto
   // Una select MAX(ID), sumando 1 para el siguiene ID valido deberia valer
   /* char* cbI = "1";
    char* cbn = "Musica Turbo-Folk de Europa del Este";
    char* cnI = "1";
    char* cnn = "Que tiene batman en el fondo de la Batcueva?";
    char* pI = "1";
    char* pn = "HorseJu";
   
    insertNewWhiteCard(db, cbn, cbI);
    
    insertNewBlackCard(db, cnn, cnI);

    insertNewPlayerData(db, pn, pI);*/

    char* whiteCard = selectWhiteCard(db, "1");
    printf("%s\n", whiteCard);
    char* blacCard = selectBlackCard(db, "1");
    printf("%s\n", blacCard);
    char* player = selectPlayer(db,"1");
    printf("%s\n", player);

    char* wcID = getLastWhiteCardID(db);
    printf("%s\n", wcID);
    char* bcID = getLastBlackCardID(db);
    printf("%s\n", bcID);
    char* pID = getLastPlayerID(db);
    printf("%s\n", pID);

    free(whiteCard);
    free(blacCard);
    free(player);
    free(wcID);
    free(bcID);
    free(pID);

    sqlite3_close(db);
    return 0;
}
