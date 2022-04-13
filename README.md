# PIV-G4
Repositorio para el proyecto de prog 4

C-MD contra la humanidad
gcc dataBaseManager.c DataBase.c sqlite3.c -L shell.c -o ..\..\Ejecutables\prueba.exe Para compilar la base de datos
Como usar la base de datos:

Crear tablas o insertar datos no requiere nada especial.
Para recibir los datos de las consultas, hace falta guardar el dato en un char* y hacer un free al final, ya que se utiliza un malloc
