#include <stdio.h>
#include "sqlite3.h"
#include <string.h>

int createDataBase(sqlite3 *db){

    
    sqlite3_stmt *statement;
    
    char sql[] = "CREATE DATABASE dataBase;";
    int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL) ;
    sqlite3_step(statement);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    return 0;
}

