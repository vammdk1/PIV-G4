#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "sqlite3.h"


int createDataBase(sqlite3 *db);
int createTables(sqlite3 *db);
int insertNewWhiteCard(sqlite3 *db, char* text, char* ID);
int insertNewBlackCard(sqlite3 *db, char* text, char* ID);
int insertNewPlayerData(sqlite3 *db, char* text, char* ID);

#endif