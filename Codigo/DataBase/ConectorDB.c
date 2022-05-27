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
    int lastIDwhite = 0;
    int lastIDBlac = 0;
    int lastIDplayer = 0;
    int lastIDgame = 0;
    char readID[4];
    char op;
    char op2;
    sqlite3* db;
    sqlite3_open("../Archivos/database.db", &db);
    
    char* whiteCard;
    char* blacCard;
    char* player ;
    char* game;
    char* wcID ;
    char* bcID;
    char* pID;

    while (op != '7') { //para leer el valor sin el ampersant
        printf("Opciones:\n1-Crear BD \n2-Crear tablas  \n3-Borrar tablas \n4-Crear carta \n5-Crear usuario \n6-Consultar datos \n7-Salir\n");
        fgets(str, 2, stdin);
        fflush(stdin);
        sscanf(str, "%s", &op); //esto se usaba para trasformar int en string 
        switch (op){
            case '1':
                createDataBase(db);
                break;
            case '2':
                createTables(db);
                break;
            case '3':
                 deleteTables(db);
                 break;
            case '4':
               
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
            
            case '5':
               
                printf("Inserta Texto: \n");
                fgets(frase, 250, stdin);
                sscanf(getLastPlayerID(db),"%i",&regresoID);
                regresoID++;
                sprintf(iDaumentado, "%i", regresoID);
                insertNewPlayerData(db, frase,iDaumentado);
                break;
            case '6':
                
                sscanf(getLastWhiteCardID(db),"%i",&lastIDwhite);
                
                //printf("%i",&LastID);
                for (int i = 1; i <= lastIDwhite; i++)
                {
                    
                    strcpy(readID, "");
                    printf("%s\n", readID);
                    sprintf(readID, "%i", i);
                    printf("%s\n", readID);
                    //sscanf(i,"%s",&Cid);
                    whiteCard = selectWhiteCard(db, readID);
                    //strcpy(whiteCard, temp);
                    printf("Carta Blanca: %s\n", whiteCard);
                }

                sscanf(getLastBlackCardID(db), "%i", &lastIDBlac);
                for (int i = 1; i <= lastIDBlac; i++)
                {
                    
                    strcpy(readID, "");
                    printf("%s\n", readID);
                    sprintf(readID, "%i", i);
                    printf("%s\n", readID);
                    //sscanf(i,"%s",&Cid);
                    blacCard = selectBlackCard(db, readID);
                    //strcpy(whiteCard, temp);
                    printf("Carta Negra: %s\n", blacCard);
                }
                sscanf(getLastPlayerID(db), "%i", &lastIDgame);
                for (int i = 1; i <= lastIDgame; i++)
                {
                    
                    strcpy(readID, "");
                    printf("%s\n", readID);
                    sprintf(readID, "%i", i);
                    printf("%s\n", readID);
                    //sscanf(i,"%s",&Cid);
                    player = selectPlayer(db, readID);
                    //strcpy(whiteCard, temp);
                    printf("Jugador: %s\n", player);
                }
                sscanf(getLastGameID(db), "%i", &lastIDgame);
                
                for (int i = 1; i <= lastIDgame; i++)
                {
                    
                    strcpy(readID, "");
                    printf("%s\n", readID);
                    sprintf(readID, "%i", i);
                    printf("%s\n", readID);
                    //sscanf(i,"%s",&Cid);
                    game = selectGameWinner(db, readID);
                    //strcpy(whiteCard, temp);
                    player = selectPlayer(db, game);
                    printf("Ganador: %s\n", player);
                }
                /*
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
                */
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
