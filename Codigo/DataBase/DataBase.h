#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "sqlite3.h"


int createDataBase(sqlite3 *db);
int createTables(sqlite3 *db);
int deleteTables(sqlite3 *db);

int insertNewWhiteCard(sqlite3 *db, char* text, char* ID);
int insertNewBlackCard(sqlite3 *db, char* text, char* ID);
int insertNewPlayerData(sqlite3 *db, char* text, char* ID);
int insertNewGameData(sqlite3 *db, char* gameID, char* playerID);
int insertNewUser(sqlite3 *db, char* nombre, char* contra, char* admin);

char* selectWhiteCard(sqlite3 *db, char* ID); //Devuelve el texto, porq el id ya lo tenemos al mandarlo
char* selectBlackCard(sqlite3 *db, char* ID);
char* selectPlayer(sqlite3 *db, char* ID);
char* selectGameWinner(sqlite3 *db, char* ID);
char* selectUser(sqlite3 *db, char* contra, char* nombre);

char* getLastWhiteCardID(sqlite3 *db);
char* getLastBlackCardID(sqlite3 *db);
char* getLastPlayerID(sqlite3 *db);
char* getLastGameID(sqlite3 *db);

#endif