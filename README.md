# PIV-G4
Repositorio para el proyecto de prog 4

C-MD contra la humanidad

¡¡¡¡ATENCION!!!!

En caso de error, primero re-compilar tanto el Servidor como el Cliente.

En caso que se de el error "disk I/O error", eliminar el archivo
database.db y regenerar la base de datos. Esto se puede dar por que la
base de datos esta abierta por otro archivo, o que esta corrupta.

=========================================================================

Comandos de Compilacion:

Compilar el Gestor de Base de Datos:
gcc ConectorDB.c DataBase.c sqlite3.c -L shell.c -o ..\..\Ejecutables\GestorDB.exe Para compilar la base de datos


Compilar el Cliente:
g++ -c Cliente.cpp -o Cliente.o
g++ -o ../../Ejecutables/Cliente.exe Cliente.o ../Estructuras/Jugador.o ../Estructuras/carta.o -l ws2_32

Compilar el Servidor
g++ -c Servidor.cpp -o Servidor.o
g++ -o ../../Ejecutables/Servidor.exe Servidor.o ../Estructuras/Jugador.o ../Estructuras/carta.o ../DataBase/DataBase.o ../DataBase/sqlite3.o -L ../DataBase/shell.o -l ws2_32

Compilar el Launcher
g++ -o ../../Ejecutables/Launcher.exe Launcher.o Admin.o Usuario.o Player.o ../Database/Database.o ../DataBase/sqlite3.o -L ../DataBase/shell.o

============================================================================
Recargado de la base de datos:

Para utilizar la base de datos, tras crear las tablas ejecutar una unica vez
el ejecutable "leeTexto.exe" para recargar las cartas a la base de datos.

Para insertar nuevas cartas de forma masiva, primero vaciar los txt y luego ejecutar leeTexto.exe