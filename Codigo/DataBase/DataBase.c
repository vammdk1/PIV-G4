#include <stdio.h>
#include <string.h>
#include "DataBase.h"

int createDataBase(sqlite3 *db){

    
    sqlite3_stmt *statement;
    
    char sql[] = "CREATE DATABASE dataBase;";
    int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL) ;
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
    int result2 = sqlite3_prepare_v2(db, sql2, -1, &statement2, NULL) ;
    sqlite3_step(statement2);
    sqlite3_finalize(statement2);

    sqlite3_stmt *statement3;
    char sql3[] = "CREATE TABLE CARTAS_NEGRAS(CARDID INT NOT NULL, TEXTO VARCHAR(250), PRIMARY KEY (CARDID));";
    int result3 = sqlite3_prepare_v2(db, sql3, -1, &statement3, NULL) ;
    sqlite3_step(statement3);
    sqlite3_finalize(statement3);

    sqlite3_stmt *statement4;
    char sql4[] = "CREATE TABLE JUGADORES(PLAYERID INT NOT NULL, NOMBRE VARCHAR(20), PRIMARY KEY (PLAYERID));";
    int result4 = sqlite3_prepare_v2(db, sql4, -1, &statement4, NULL) ;
    sqlite3_step(statement4);
    sqlite3_finalize(statement4);

/*
    sqlite3_stmt *statement5;
    char sql5[] = "CREATE TABLE CARTAS_BLANCAS(CARDID INT NOT NULL, TEXTO VARCHAR(250), PRIMARY KEY (CARDID));";
    int result5 = sqlite3_prepare_v2(db, sql5, -1, &statement5, NULL) ;
    sqlite3_step(statement5);
    sqlite3_finalize(statement5);
*/
}

int insertNewWhiteCard(sqlite3 *db, char* text, char* ID){
    sqlite3_stmt *statement;
    char sql[] = "INSERT INTO CARTAS_BLANCAS(CARDID, TEXTO) VALUES (";
    strcat(sql,ID);
    strcat(sql,",'");
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
    char sql[] = "INSERT INTO CARTAS_NEGRAS(CARDID, TEXTO) VALUES (";
    strcat(sql,ID);
    strcat(sql,",'");
    strcat(sql,text);
    strcat(sql,"');");
    printf("%s", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, NULL);
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
    char sql[] = "INSERT INTO JUGADORES(PLAYERID, NOMBRE) VALUES(";
    strcat(sql,ID);
    strcat(sql,",'");
    strcat(sql,text);
    strcat(sql,"');");
    printf("%s", sql);
    int result = sqlite3_prepare_v2(db,sql,-1,&statement, NULL);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
    if(result != SQLITE_OK){
        printf("Error\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
    return 0;
}

