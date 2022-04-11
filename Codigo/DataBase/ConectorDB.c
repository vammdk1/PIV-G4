#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DataBase.h"
#include "../Estructuras/carta.h"
#include "../Estructuras/jugador.h"
#include "../Estructuras/baraja.h"

int main(int argc, char const* argv[])
{
    int regresoID=0;
    char frase[250];
    char str[1];
    char op;
    sqlite3* db;
    sqlite3_open("../Archivos/database.db", &db);

    while (op != '8') { //para leer el valor sin el ampersant
        printf("Opciones:\n 1-Crear BD \n 2-Borrar base de datos \n 3- crear tablas  \n 4- Borrar tablas \n 5-Crear carta \n 6- Crear usuario \n 7- Consultar datos \n 8- Salir\n");
        fgets(str, 1, stdin);
        sscanf(str, "%c", &op); // para asignar el valor usamros el ampersant
        if (op == '1') {
            createDataBase(db);
        }else if (op == '2' ) {
            //borrarDataBase(db);//crear 
            free(db);
            db=NULL;
        }else if (op == '3' ) {
            createTables(db);
        }else if (op == '4' ) {
           deleteTables(db);
        }
        else if (op == '5' ) {
            Carta c;
            
            printf("Inserta Texto: \n");
            fgets(frase, 250, stdin);
            sscanf(frase, "%s", &c.texto);
            printf("1-Carta negra \n 2-Carta blanca \n");
            fgets(str, 2, stdin);
            sscanf(str, "%c", &op);
            if(op=='1'){
                sscanf(getLastBlackCardID(db),"%i",regresoID);
                c.negra=0;
                insertNewBlackCard(db, c.texto, regresoID+1);
            }else if (op=='2')
            {
                sscanf(getLastWhiteCardID(db),"%i",regresoID);
                c.negra=1;
                insertNewWhiteCard(db, c.texto, regresoID+1);
            }else{
                printf("No se ha introducido ninguna opcion correcta");
            }
            
        }else if (op == '6' ) {
            char* pn;
            printf("Inserta Texto: \n");
            fgets(frase, 250, stdin);
            sscanf(frase, "%s", &pn);
            sscanf(getLastPlayerID(db),"%i",regresoID);
            insertNewPlayerData(db, pn, regresoID+1);
        }else if (op == '7' ) {
            char* whiteCard = selectWhiteCard(db, "1");
            printf("%s\n", whiteCard);
            char* blacCard = selectBlackCard(db, "1");
            printf("%s\n", blacCard);
            char* player = selectPlayer(db, "1");
            printf("%s\n", player);

            char* wcID = getLastWhiteCardID(db);
            printf("%s\n", wcID);
            char* bcID = getLastBlackCardID(db);
            printf("%s\n", bcID);
            char* pID = getLastPlayerID(db);
            printf("%s\n", pID);
        }
        
    }

    createDataBase(db);
    createTables(db);
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

     insertNewPlayerData(db, pn, pI);*

    char* whiteCard = selectWhiteCard(db, "1");
    printf("%s\n", whiteCard);
    char* blacCard = selectBlackCard(db, "1");
    printf("%s\n", blacCard);
    char* player = selectPlayer(db, "1");
    printf("%s\n", player);

    char* wcID = getLastWhiteCardID(db);
    printf("%s\n", wcID);
    char* bcID = getLastBlackCardID(db);
    printf("%s\n", bcID);
    char* pID = getLastPlayerID(db);
    printf("%s\n", pID);*/

    free(whiteCard);
    free(blacCard);
    free(player);
    free(wcID);
    free(bcID);
    free(pID);

    sqlite3_close(db);
    return 0;
}
