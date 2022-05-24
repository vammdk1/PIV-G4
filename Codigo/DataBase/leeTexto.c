#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataBase.h"
//Lee un texto dado, creando una carta por linea
// f es el archivo a leer
void cogerCartas(FILE* f, int tipoCarta)
{
    sqlite3* db;
    sqlite3_open("../Archivos/database.db", &db);
    int id = 1;
    char* frase = NULL;
    size_t len = 0;
    char** cartas;
    char** temp = (char**) malloc(sizeof(char*)*100);

    while (getline(&frase, &len, f) != -1){
        printf("%i - %s\n",id, frase);
        temp[id-1] = (char*) malloc(sizeof(char)*strlen(frase)+1); 
        strcpy(temp[id-1], frase);
        id++;
        
    }
   
    cartas = (char**) malloc(sizeof(char*)*id);
   
    for (int i = 0; i < id-1; i++)
    {
        
        cartas[i] = (char*) malloc(sizeof(char)*250);
        
        strcpy(cartas[i],temp[i]);
        printf("%s\n",cartas[i]);
        char iDaumentado[4];
        if(tipoCarta){
            //negras
            int regresoID = 0;
            sscanf(getLastBlackCardID(db),"%i",&regresoID);
            regresoID++;
            sprintf(iDaumentado, "%i", regresoID);
            insertNewBlackCard(db, cartas[i],iDaumentado);
        } else {
            //blancas
           
            int regresoID = 0;
            sscanf(getLastWhiteCardID(db),"%i",&regresoID);
            regresoID++;
            sprintf(iDaumentado, "%i", regresoID);
            insertNewWhiteCard(db, cartas[i],iDaumentado);

        }
        
    }

    

    
    /*for(int i = 0; i<100;i++){
        free(temp[i]);
    }*/
    
    free(temp);
    
    printf("\n");
}


int main(int argc, char const *argv[])
{
    printf("cartas blancas\n");
    FILE* f = fopen("../Archivos/cartasBlancas.txt", "r");
    cogerCartas(f, 0);
    fclose(f);
    printf("cartas negras\n");
    FILE* f2 = fopen("../Archivos/cartasNegras.txt", "r");
    cogerCartas(f2, 1);
    fclose(f2);
    sqlite3* db;
    sqlite3_open("../Archivos/database.db", &db);
   
    
    return 0;
}
