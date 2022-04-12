#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DataBase.h"

int main(int argc, char const* argv[])
{
    int regresoID=0;
    char iDaumentado[4];
    char frase[250];
    char str[2];
    char op;
    char op2;
    sqlite3* db;
    sqlite3_open("../Archivos/database.db", &db);

    while (op != '8') { //para leer el valor sin el ampersant
        char whiteCard[250];
        printf("Opciones:\n1-Crear BD \n2-Borrar base de datos \n3-crear tablas  \n4-Borrar tablas \n5-Crear carta \n6-Crear usuario \n7-Consultar datos \n8-Salir\n");
        fgets(str, 2, stdin);
        fflush(stdin);
        sscanf(str, "%s", &op); //esto se usaba para trasformar int en string 
        switch (op){
            case '1':
                createDataBase(db);
                break;
            case '2':
                //borrarDataBase(db);//crear 
                free(db);
                db=NULL;
                break;
            case '3':
                createTables(db);
                break;
            case '4':
                 deleteTables(db);
                 break;
            case '5':
               
                printf("Inserta Texto: \n");
                fgets(frase, 250, stdin);
                //sscanf(frase, "%s", &textoC);
                printf("1-Carta negra \n2-Carta blanca \n");
                fgets(str, 2, stdin);
                sscanf(str, "%s", &op2);
                fflush(stdin);
                switch (op2){
                    case '1':
                        sscanf(getLastBlackCardID(db),"%i",&regresoID);
                        regresoID++;
                        //printf("Total: %i\n",regresoID);
                        sprintf(iDaumentado, "%c", regresoID);
                        insertNewBlackCard(db, frase,iDaumentado);
                        break;
                    case '2':
                        sscanf(getLastWhiteCardID(db),"%i",&regresoID);
                        insertNewWhiteCard(db,frase,(char*)regresoID+1);
                        break;
                    default:
                        printf("ninguna elcción hecha\n");
                        break;
                    }
                break;
            
            case '6':
               
                printf("Inserta Texto: \n");
                fgets(frase, 250, stdin);
                //sscanf(frase, "%s", &pn);
                sscanf(getLastPlayerID(db),"%i",&regresoID);
                insertNewPlayerData(db, frase, (char*)regresoID+1);
                break;
            case '7':
                
                
                strcpy(whiteCard, selectWhiteCard(db, "1"));
                printf("%s\n", whiteCard);
                /*char* blacCard = selectBlackCard(db, "1");
                printf("%s\n", blacCard);
                char* player = selectPlayer(db, "1");
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
                break;*/
                
        }
    }

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
    printf("%s\n", pID);

    free(whiteCard);
    free(blacCard);
    free(player);
    free(wcID);
    free(bcID);
    free(pID);*/

    sqlite3_close(db);
    return 0;
}
