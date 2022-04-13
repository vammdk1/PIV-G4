#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DataBase.h"

int createDataBase(sqlite3 *db){

    
    sqlite3_stmt *statement;
    
    char sql[] = "CREATE DATABASE dataBase;";
    int result = sqlite3_prepare_v2(db, sql, -1, &statement, 0) ;
    printf("%s\n", sql);
    sqlite3_step(statement);
   
   sqlite3_finalize(statement);

 if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
    return 0;
}

int createTables(sqlite3 *db){
     //Crear las cuatro tablas
    sqlite3_stmt *statement2;
    char sql2[] = "CREATE TABLE CARTAS_BLANCAS(CARDID INT NOT NULL, TEXTO VARCHAR(250), PRIMARY KEY (CARDID));";
    int result2 = sqlite3_prepare_v2(db, sql2, -1, &statement2, 0) ;
    sqlite3_step(statement2);
    sqlite3_finalize(statement2);

    sqlite3_stmt *statement3;
    char sql3[] = "CREATE TABLE CARTAS_NEGRAS(CARDID INT NOT NULL, TEXTO VARCHAR(250), PRIMARY KEY (CARDID));";
    int result3 = sqlite3_prepare_v2(db, sql3, -1, &statement3, 0) ;
    sqlite3_step(statement3);
    sqlite3_finalize(statement3);

    sqlite3_stmt *statement4;
    char sql4[] = "CREATE TABLE JUGADORES(PLAYERID INT NOT NULL, NOMBRE VARCHAR(20), PRIMARY KEY (PLAYERID));";
    int result4 = sqlite3_prepare_v2(db, sql4, -1, &statement4, 0) ;
    sqlite3_step(statement4);
    
    sqlite3_finalize(statement4);

    sqlite3_stmt *statement5;
    char sql5[] = "CREATE TABLE PARTIDAS(GAMEID INT NOT NULL, WINNER INT, PRIMARY KEY (GAMEID), FOREIGN KEY(WINNER) REFERENCES JUGADORES(PLAYERID));";
    printf("%s\n", sql5);
    int result5 = sqlite3_prepare_v2(db, sql5, -1, &statement5, 0) ;
    sqlite3_step(statement5);
    sqlite3_finalize(statement5);

   

}
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

}

int insertNewWhiteCard(sqlite3 *db, char* text, char* ID){
    sqlite3_stmt *statement;
   
    char sql[250] = " ";
    strcat(sql, "INSERT INTO CARTAS_BLANCAS(CARDID, TEXTO) VALUES (");
    strcat(sql,ID);
    strcat(sql,", '");
    strcat(sql,text);
    strcat(sql,"');");
    printf("%s\n", sql);
  

    int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL) ;

    
    sqlite3_step(statement);
    sqlite3_finalize(statement);
  

    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
    
    return 0;
    

}


int insertNewBlackCard(sqlite3 *db, char* text, char* ID){
    sqlite3_stmt *statement;
    char sql[250] = " "; //Si no ponemos esto se concatena con el anterior
    strcat(sql, "INSERT INTO CARTAS_NEGRAS(CARDID, TEXTO) VALUES (");
    strcat(sql,ID);
    strcat(sql,",'");
    strcat(sql,text);
    strcat(sql,"');");
    printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
    return 0;

}
int insertNewPlayerData(sqlite3 *db, char* text, char* ID){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "INSERT INTO JUGADORES(PLAYERID, NOMBRE) VALUES(");
    strcat(sql,ID);
    strcat(sql,",'");
    strcat(sql,text);
    strcat(sql,"');");
    printf("%s\n", sql);
    printf("prueba1");
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
    printf("prueba2");
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
    printf("prueba3");
    return 0;
}

int insertNewGameData(sqlite3 *db, char* gameID, char* playerID){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "INSERT INTO PARTIDAS(GAMEID, WINNER) VALUES(");
    strcat(sql,gameID);
    strcat(sql,",");
    strcat(sql,playerID);
    strcat(sql,");");
    printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
    return 0;
}

char* selectWhiteCard(sqlite3 *db, char* ID){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT TEXTO FROM CARTAS_BLANCAS WHERE CARDID = ");
    strcat(sql,ID);
    strcat(sql,";");
    printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    const char* text = sqlite3_column_text(statement,0);
    
       
    
    char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
    strcpy(ret, text);
    sqlite3_finalize(statement);
    
    
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return "error";
    }
    
  
    return ret;
}
char* selectBlackCard(sqlite3 *db, char* ID){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT TEXTO FROM CARTAS_NEGRAS WHERE CARDID = ");
    strcat(sql,ID);
    strcat(sql,";");
    printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    const char* text = sqlite3_column_text(statement,0);
    
       
    
    char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
    strcpy(ret, text);
    sqlite3_finalize(statement);
    
    
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return "error";
    }
    
  
    return ret;
}
char* selectPlayer(sqlite3 *db, char* ID){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT NOMBRE FROM JUGADORES WHERE PLAYERID = ");
    strcat(sql,ID);
    strcat(sql,";");
    printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    const char* text = sqlite3_column_text(statement,0);
    
       
    
    char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
    strcpy(ret, text);
    sqlite3_finalize(statement);
    
    
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return "error";
    }
    
  
    return ret;
}

char* selectGameWinner(sqlite3 *db, char* ID){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT WINNER FROM PARTIDAS WHERE GAMEID = ");
    strcat(sql,ID);
    strcat(sql,";");
    printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    const char* text = sqlite3_column_text(statement,0);
    
       
    
    char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
    strcpy(ret, text);
    sqlite3_finalize(statement);
    
    
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return "error";
    }
    
  
    return ret;
}

char* getLastWhiteCardID(sqlite3 *db){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT MAX(CARDID) FROM CARTAS_BLANCAS;");
    printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    const char* text = sqlite3_column_text(statement,0);
    
       
    
    char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
    strcpy(ret, text);
    sqlite3_finalize(statement);
    
    
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return "error";
    }
    
  
    return ret;
}
char* getLastBlackCardID(sqlite3 *db){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT MAX(CARDID) FROM CARTAS_NEGRAS;");
    printf("%s\n", sql);
   
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    const char* text = sqlite3_column_text(statement,0);
    printf("%i\n",strlen(text));
       
    
    char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
         

    strcpy(ret, text);

    sqlite3_finalize(statement);

    
     
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return "error";
    }
    
 
    return ret;
}
char* getLastPlayerID(sqlite3 *db){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT MAX(PLAYERID) FROM JUGADORES;");
    printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    const char* text = sqlite3_column_text(statement,0);
    
       
    
    char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
    strcpy(ret, text);
    sqlite3_finalize(statement);
    
    
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return "error";
    }
    
  
    return ret;
}

char* getLastGameID(sqlite3 *db){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT MAX(GAMEID) FROM PARTIDAS;");
    printf("%s\n", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, 0);
    sqlite3_step(statement);
    const char* text = sqlite3_column_text(statement,0);
    
       
    
    char* ret = (char*) malloc(sizeof(char)*strlen(text)+1);
    strcpy(ret, text);
    sqlite3_finalize(statement);
    
    
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return "error";
    }
    
  
    return ret;
}
