#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DataBase.h"

//Crea la base de datos junto al archivo.
//*db es el puntero a la base de datos
int createDataBase(sqlite3 *db){

    
    sqlite3_stmt *statement;
    
    char sql[] = "CREATE DATABASE dataBase;";
    int result = sqlite3_prepare_v2(db, sql, -1, &statement, 0) ;
    //printf("%s\n", sql);
    sqlite3_step(statement);
   
   sqlite3_finalize(statement);

 if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
    printf("Base de datos creada\n");
    return 0;
}

//Crea las tablas de la base de datos, incluyendo valores por defecto para evtiar errores de lectura
int createTables(sqlite3 *db){
     //Crear las cuatro tablas
    sqlite3_stmt *statement2;
    char sql2[] = "CREATE TABLE CARTAS_BLANCAS(CARDID INT NOT NULL, TEXTO VARCHAR(250), PRIMARY KEY (CARDID));";
    int result2 = sqlite3_prepare_v2(db, sql2, -1, &statement2, 0) ;
    sqlite3_step(statement2);
    sqlite3_finalize(statement2);
    insertNewWhiteCard(db, "NO SALIR", "0");

    sqlite3_stmt *statement3;
    char sql3[] = "CREATE TABLE CARTAS_NEGRAS(CARDID INT NOT NULL, TEXTO VARCHAR(250), PRIMARY KEY (CARDID));";
    int result3 = sqlite3_prepare_v2(db, sql3, -1, &statement3, 0) ;
    sqlite3_step(statement3);
    sqlite3_finalize(statement3);
    insertNewBlackCard(db, "NO SALIR", "0");

    sqlite3_stmt *statement4;
    char sql4[] = "CREATE TABLE JUGADORES(PLAYERID INT NOT NULL, NOMBRE VARCHAR(20), PRIMARY KEY (PLAYERID));";
    int result4 = sqlite3_prepare_v2(db, sql4, -1, &statement4, 0) ;
    sqlite3_step(statement4);
    
    sqlite3_finalize(statement4);
    insertNewPlayerData(db, "NO SALIR", "0");

    sqlite3_stmt *statement5;
    char sql5[] = "CREATE TABLE PARTIDAS(GAMEID INT NOT NULL, WINNER INT, PRIMARY KEY (GAMEID), FOREIGN KEY(WINNER) REFERENCES JUGADORES(PLAYERID));";
    //printf("%s\n", sql5);
    int result5 = sqlite3_prepare_v2(db, sql5, -1, &statement5, 0) ;
    sqlite3_step(statement5);
    sqlite3_finalize(statement5);
    insertNewGameData(db, "0","0");

     sqlite3_stmt *statement6;
    char sql6[] = "CREATE TABLE USUARIOS(CONTRA VARCHAR(50) NOT NULL, NOMBRE VARCHAR(50), ADMIN INT NOT NULL, PRIMARY KEY (CONTRA));";
    int result6 = sqlite3_prepare_v2(db, sql6, -1, &statement6, 0) ;
    sqlite3_step(statement6);
    sqlite3_finalize(statement6);
   
    insertNewUser(db, "No", "Salir", "0");
    

   printf("Tablas creadas\n");

}

//Elimina las tablas existentes
int deleteTables(sqlite3 *db){
 sqlite3_stmt *statement2;
    char sql2[] = "DROP TABLE CARTAS_BLANCAS;";
    int result2 = sqlite3_prepare_v2(db, sql2, -1, &statement2, 0) ;
    sqlite3_step(statement2);
    sqlite3_finalize(statement2);

    sqlite3_stmt *statement3;
    char sql3[] = "DROP TABLE CARTAS_NEGRAS;";
    int result3 = sqlite3_prepare_v2(db, sql3, -1, &statement3, 0) ;
    sqlite3_step(statement3);
    sqlite3_finalize(statement3);

    sqlite3_stmt *statement4;
    char sql4[] = "DROP TABLE JUGADORES;";
    int result4 = sqlite3_prepare_v2(db, sql4, -1, &statement4, 0) ;
    sqlite3_step(statement4);
    
    sqlite3_finalize(statement4);
    
    sqlite3_stmt *statement5;
    char sql5[] = "DROP TABLE PARTIDAS;";
    int result5 = sqlite3_prepare_v2(db, sql5, -1, &statement5, 0) ;
    sqlite3_step(statement5);
    sqlite3_finalize(statement5);

    sqlite3_stmt *statement6;
    char sql6[] = "DROP TABLE USUARIOS;";
    int result6 = sqlite3_prepare_v2(db, sql6, -1, &statement6, 0) ;
    sqlite3_step(statement6);
    sqlite3_finalize(statement6);
    

    printf("Tablas Eliminadas\n");

}

//Inserta una nueva carta blanca
//text -> Texto a insertar en la carta
//ID -> numero con la identificacion
int insertNewWhiteCard(sqlite3 *db, char* text, char* ID){
    sqlite3_stmt *statement;
   
    char sql[250] = " ";
    strcat(sql, "INSERT INTO CARTAS_BLANCAS(CARDID, TEXTO) VALUES (");
    strcat(sql,ID);
    strcat(sql,", '");
    strcat(sql,text);
    strcat(sql,"');");
   // printf("%s\n", sql);
  

    int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL) ;

    
    sqlite3_step(statement);
    sqlite3_finalize(statement);
  

    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
    
    printf("Carta Insertada\n");
    return 0;
    

}

//Inserta una nueva carta negra
//text -> Texto a insertar en la carta
//ID -> numero con la identificacion
int insertNewBlackCard(sqlite3 *db, char* text, char* ID){
    sqlite3_stmt *statement;
    char sql[250] = " "; //Si no ponemos esto se concatena con el anterior
    strcat(sql, "INSERT INTO CARTAS_NEGRAS(CARDID, TEXTO) VALUES (");
    strcat(sql,ID);
    strcat(sql,",'");
    strcat(sql,text);
    strcat(sql,"');");
    //printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }

    printf("Carta Insertada\n");
    return 0;

}
//Inserta un jugador a la base de datis
//text -> Nombre dek jugador
//ID -> numero con la identificacion
int insertNewPlayerData(sqlite3 *db, char* text, char* ID){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "INSERT INTO JUGADORES(PLAYERID, NOMBRE) VALUES(");
    strcat(sql,ID);
    strcat(sql,",'");
    strcat(sql,text);
    strcat(sql,"');");
   // printf("%s\n", sql);
   
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
   
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }

    printf("Jugador Insertado\n");
    
    return 0;
}

//Inserta una nueva partida
//gameID -> Identificador de la partida
//playerID -> Identificador del jugador ganador
int insertNewGameData(sqlite3 *db, char* gameID, char* playerID){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "INSERT INTO PARTIDAS(GAMEID, WINNER) VALUES(");
    strcat(sql,gameID);
    strcat(sql,",");
    strcat(sql,playerID);
    strcat(sql,");");
   // printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }

    printf("Partida Insertada\n");
    return 0;
}
int insertNewUser(sqlite3 *db,char* nombre,char* contra,char* admin){
    sqlite3_stmt *statement;
   
    char sql[250] = " ";
    strcat(sql, "INSERT INTO USUARIOS(CONTRA, NOMBRE, ADMIN) VALUES ('");
    strcat(sql,contra);
    strcat(sql,"', '");
    strcat(sql,nombre);
    strcat(sql,"', ");
    strcat(sql,admin);
    strcat(sql,");");
    int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL) ;

    
    sqlite3_step(statement);
    sqlite3_finalize(statement);
  

    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
    
    printf("Usuario Insertado\n");
    return 0;
}

//Selecciona una carta blanca
//ID -> Identificador de la carta
char* selectWhiteCard(sqlite3 *db, char* ID){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT TEXTO FROM CARTAS_BLANCAS WHERE CARDID = ");
    strcat(sql,ID);
    strcat(sql,";");
    //printf("%s\n", sql);
    
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    if(result != SQLITE_OK){
         printf("Error\n");
         printf("%s\n", sqlite3_errmsg(db));
          return "error";
        }
    
    if(sqlite3_step(statement) == SQLITE_ROW){
        
        
        const char* text = sqlite3_column_text(statement,0);
    
       
    
        char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
        strcpy(ret, text);
        sqlite3_finalize(statement);
    
    
       
    
  
        return ret;
    }
    
    return "error";
    
}

//Selecciona una carta negra
//ID -> Identificador de la carta deseada
char* selectBlackCard(sqlite3 *db, char* ID){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT TEXTO FROM CARTAS_NEGRAS WHERE CARDID = ");
    strcat(sql,ID);
    strcat(sql,";");
    //printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    if(result != SQLITE_OK){
         printf("Error\n");
         printf("%s\n", sqlite3_errmsg(db));
          return "error";
        }
    
    if(sqlite3_step(statement) == SQLITE_ROW){
        
        
        const char* text = sqlite3_column_text(statement,0);
    
       
    
        char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
        strcpy(ret, text);
        sqlite3_finalize(statement);
    
    
     
    
  
        return ret;
    }
    
    return "error";
}

//Selecciona al jugador
//ID -> Identificador del jugador
char* selectPlayer(sqlite3 *db, char* ID){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT NOMBRE FROM JUGADORES WHERE PLAYERID = ");
    strcat(sql,ID);
    strcat(sql,";");
   // printf("%s\n", sql);
   int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    if(result != SQLITE_OK){
         printf("Error\n");
         printf("%s\n", sqlite3_errmsg(db));
          return "error";
        }
    
    if(sqlite3_step(statement) == SQLITE_ROW){
        
        
        const char* text = sqlite3_column_text(statement,0);
    
       
    
        char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
        strcpy(ret, text);
        sqlite3_finalize(statement);
    
    
     
    
  
        return ret;
    }
    
    return "error";
}

//Selecciona el jugador ganador de la partida
//ID -> Identificador de la partida
char* selectGameWinner(sqlite3 *db, char* ID){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT WINNER FROM PARTIDAS WHERE GAMEID = ");
    strcat(sql,ID);
    strcat(sql,";");
   // printf("%s\n", sql);
   int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    if(result != SQLITE_OK){
         printf("Error\n");
         printf("%s\n", sqlite3_errmsg(db));
          return "error";
        }
    
    if(sqlite3_step(statement) == SQLITE_ROW){
        
        
        const char* text = sqlite3_column_text(statement,0);
    
       
    
        char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
        strcpy(ret, text);
        sqlite3_finalize(statement);
    
    
     
    
  
        return ret;
    }
    
    return "error";
}
char* selectUser(sqlite3 *db, char* contra, char* nombre){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT ADMIN FROM USUARIOS WHERE CONTRA = '");
    strcat(sql,contra);
    strcat(sql,"' AND NOMBRE = '");
    strcat(sql,nombre);
    strcat(sql, "';");
    
    
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    if(result != SQLITE_OK){
         printf("Error\n");
         printf("%s\n", sqlite3_errmsg(db));
          return "error";
        }
    
    if(sqlite3_step(statement) == SQLITE_ROW){
        
        
        const char* text = sqlite3_column_text(statement,0);
       
       
    
        char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
        strcpy(ret, text);
        sqlite3_finalize(statement);
    
    
       
    
  
        return ret;
    }
    
    return "error";
}

//Selecciona el ultimo identificador incluido en la tabla Cartas_Blancas
char* getLastWhiteCardID(sqlite3 *db){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT MAX(CARDID) FROM CARTAS_BLANCAS;");
    //printf("%s\n", sql);

    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    if(result != SQLITE_OK){
         printf("Error\n");
         printf("%s\n", sqlite3_errmsg(db));
          return "error";
        }
    
    if(sqlite3_step(statement) == SQLITE_ROW){
        
        
        const char* text = sqlite3_column_text(statement,0);

    
        char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
        strcpy(ret, text);
        sqlite3_finalize(statement);
    
  
        return ret;
    }
    
    return "0";
    
}
//Selecciona el ultimo identificador incluido en la tabla Cartas_Negras
char* getLastBlackCardID(sqlite3 *db){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT MAX(CARDID) FROM CARTAS_NEGRAS;");
    //printf("%s\n", sql);
   
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    if(result != SQLITE_OK){
         printf("Error\n");
         printf("%s\n", sqlite3_errmsg(db));
          return "error";
        }
    
    if(sqlite3_step(statement) == SQLITE_ROW){
        
        
        const char* text = sqlite3_column_text(statement,0);

        char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
        strcpy(ret, text);
        sqlite3_finalize(statement);
  
        return ret;
    }
    
    return "0";
}
//Selecciona el ultimo identificador incluido en la tabla Jugadores
char* getLastPlayerID(sqlite3 *db){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT MAX(PLAYERID) FROM JUGADORES;");
   // printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    if(result != SQLITE_OK){
         printf("Error\n");
         printf("%s\n", sqlite3_errmsg(db));
          return "error";
        }
    
    if(sqlite3_step(statement) == SQLITE_ROW){
        
        
        const char* text = sqlite3_column_text(statement,0);

        char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
        strcpy(ret, text);
        sqlite3_finalize(statement);

        return ret;
    }
    
    return "error";
}
//Selecciona el ultimo identificador incluido en la tabla Partidas
char* getLastGameID(sqlite3 *db){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT MAX(GAMEID) FROM PARTIDAS;");
   // printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    if(result != SQLITE_OK){
         printf("Error\n");
         printf("%s\n", sqlite3_errmsg(db));
          return "error";
        }
    
    if(sqlite3_step(statement) == SQLITE_ROW){
        
        
        const char* text = sqlite3_column_text(statement,0);

        char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
        strcpy(ret, text);
        sqlite3_finalize(statement);

        return ret;
    }
    
    return "error";
}
