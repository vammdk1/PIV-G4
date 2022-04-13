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
    
    char* whiteCard;
    char* blacCard;
    char* player ;
    char* wcID ;
    char* bcID;
    char* pID;

    while (op != '8') { //para leer el valor sin el ampersant
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
                        sprintf(iDaumentado, "%i", regresoID);
                        insertNewBlackCard(db, frase,iDaumentado);
                        break;
                    case '2':
                        sscanf(getLastWhiteCardID(db),"%i",&regresoID);
                        regresoID++;
                        sprintf(iDaumentado, "%i", regresoID);
                        insertNewWhiteCard(db, frase,iDaumentado);
                        break;
                    default:
                        printf("ninguna elcción hecha\n");
                        break;
                    }
                break;
            
            case '6':
               
                printf("Inserta Texto: \n");
                fgets(frase, 250, stdin);
                sscanf(getLastPlayerID(db),"%i",&regresoID);
                regresoID++;
                sprintf(iDaumentado, "%i", regresoID);
                insertNewPlayerData(db, frase,iDaumentado);
                break;
            case '7':
                
                
                strcpy(whiteCard, selectWhiteCard(db, "1"));
                printf("Carta Blanca: %s\n", whiteCard);
                blacCard = selectBlackCard(db, "1");
                printf("%s\n", blacCard);
                player = selectPlayer(db, "1");
                printf("%s\n", player);
                wcID = getLastWhiteCardID(db);
                printf("%s\n", wcID);
                bcID = getLastBlackCardID(db);
                printf("%s\n", bcID);
                pID = getLastPlayerID(db);
                printf("%s\n", pID);
                break;
                
        }
    }
    free(whiteCard);
    free(blacCard);
    free(player);
    free(wcID);
    free(bcID);
    free(pID);

    sqlite3_close(db);
    return 0;
}
