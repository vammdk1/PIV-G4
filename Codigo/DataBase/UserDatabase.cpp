#include "UserDatabase.h"

UserDatabase::UserDatabase(std::string ruta){
    sqlite3_open(ruta.c_str(), &this->db);
}
UserDatabase::~UserDatabase(){
    
}


int UserDatabase::createDataBase(){
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
int UserDatabase::createTables(){
    sqlite3_stmt *statement2;
    char sql2[] = "CREATE TABLE USUARIOS(CONTRA VARCHAR(50) NOT NULL, NOMBRE VARCHAR(50), ADMIN INT NOT NULL, PRIMARY KEY (CONTRA));";
    int result2 = sqlite3_prepare_v2(db, sql2, -1, &statement2, 0) ;
    sqlite3_step(statement2);
    sqlite3_finalize(statement2);
   
    insertNewUser("No", "Salir", 0);
    std::cout << "Tablas creadas" << std::endl;
}
int UserDatabase::deleteTables(){
    char sql2[] = "DROP TABLE USUARIOS;";
    int result2 = sqlite3_prepare_v2(db, sql2, -1, &statement2, 0) ;
    sqlite3_step(statement2);
    sqlite3_finalize(statement2);
    std::cout << "Tablas eliminadas" << std::endl;
}

int UserDatabase::insertNewUser(char* nombre, char* contra, char* admin){
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

//Devuelve si el usuario pedido es admin
char* UserDatabase::selectUser(char* contra, char* nombre){
    sqlite3_stmt *statement;
    char sql[250] = " ";
    strcat(sql, "SELECT ADMIN FROM USUARIOS WHERE CONTRA = '");
    strcat(sql,contra);
    strcat(sql,"' AND NOMBRE = '");
    strcat(sql,nombre);
    strcat(sql, "';");
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