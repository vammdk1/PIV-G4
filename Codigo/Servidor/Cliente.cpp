// IMPORTANT: Winsock Library ("ws2_32") should be linked
extern "C"{
    #include <stdio.h>
    #include <winsock2.h>
	#include "../Estructuras/jugador.h"
	//#include "../Estructuras/carta.h"
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

void cabecera(){
	cout<<"+------------------------------------+"<<endl;
	cout<<"|+----------------------------------+|"<<endl;
	cout<<"||                                  ||"<<endl;
	cout<<"||     CMD CONTRA LA HUMANIDAD      ||"<<endl;
	cout<<"||                                  ||"<<endl;
	cout<<"++----------------------------------++"<<endl;
	cout<<"++----------------------------------++"<<endl;
}
void LineaJugador(Jugador* nombres[], int longitud){
	for(int i=0;i<longitud;i++){
		if(nombres[i]->esRey()){
			cout<<"||"<<nombres[i]->getNombre()<<"||"<<nombres[i]->getPuntos()<<"||*||"<<endl;
		}else{
			cout<<"||"<<nombres[i]->getNombre()<<"||"<<nombres[i]->getPuntos()<<"|| ||"<<endl;
		}
		
	}
	
	}

void LineaConsola(){
	cout<<"++-----------+----------+-----------++"<<endl;
	cout<<"|| Jugadores | Puntos   |   Rey     ||"<<endl;
	cout<<"--------------------------------------"<<endl;
}

int main(int argc, char *argv[]) {

    char* SERVER_IP;
    int SERVER_PORT = 6000;
    std::ifstream myfile;
    myfile.open("../Archivos/.config");
    
    int lineNumber = 0;
    for( std::string line; getline( myfile, line ); )
    {
        if(lineNumber == 0){
           SERVER_IP = new char[strlen(line.c_str())+1];
           strcpy(SERVER_IP, line.c_str());
        } else {
            stringstream ss;
            ss << line;
            ss >> SERVER_PORT;
        }
        lineNumber++;
        //out << line << endl;
    }
    myfile.close();
    std::ofstream loggerFile;
	loggerFile.open("../Archivos/Logger.txt");

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];
	char str[50];

	//printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout<<"Failed. Error Code : "<< WSAGetLastError()<<endl;
		return -1;
	}
	

	//printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout<<"Could not create socket : "<< WSAGetLastError()<<endl;
		WSACleanup();
		return -1;
	}

	//printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		cout<<"Connection error: "<<WSAGetLastError()<<endl;
		closesocket(s);
		WSACleanup();
		return -1;
	}

	//printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
	//ntohs(server.sin_port));

	//Fase 1
	
	cout<<"Introduce el numero de jugadores: "<<endl;
	fgets(str, 2, stdin);
	fflush(stdin);
	strcpy(sendBuff, str);
	send(s, sendBuff, sizeof(sendBuff), 0); //1a
	loggerFile << "Numero de jugadores: " << str << "\n";
	bool final=false;
	int NJ ;
	sscanf(str, "%i",&NJ);
	while(!final){
		//fase1
		recv(s, recvBuff, sizeof(recvBuff), 0);
		if(strcmp(recvBuff, "Nombre del jugador") == 0){
			loggerFile << "Introducir jugador \n";
			cout<<"Introduce el nombre del jugador: "<<endl;
			fgets(str, 20, stdin);
			fflush(stdin);
			strcpy(sendBuff, str);
			send(s, sendBuff, sizeof(sendBuff), 0);
		}else if(strcmp(recvBuff, "inicio F2") == 0){
			loggerFile << "Inicio Fase 2\n";
			while(true){
				recv(s, recvBuff, sizeof(recvBuff), 0);
				if(strcmp(recvBuff, "Que carta elijes? :") == 0){
					cout<<recvBuff<<endl;
					fgets(str, 2, stdin);
					fflush(stdin);
					strcpy(sendBuff, str);
					send(s, sendBuff, sizeof(sendBuff), 0);
					loggerFile << "Eleccion de carta: " << sendBuff << "\n";
				}else if(strcmp(recvBuff, "Rey") == 0){
					do
					{
						recv(s, recvBuff, sizeof(recvBuff), 0);
						if(strcmp(recvBuff, "Que carta gana? :") == 0){
							cout<< recvBuff<<endl;
							fgets(str, 2, stdin);
							fflush(stdin);
							strcpy(sendBuff, str);
							send(s, sendBuff, sizeof(sendBuff), 0);
							loggerFile << "Eleccion de carta: " << sendBuff << "\n";
							break;
						}else{	
							cout << recvBuff<<endl;
							send(s, "Confirmacion de cartas", sizeof(sendBuff), 0);
							loggerFile << "Carta leida\n";
							}

					} while (true);
				}else if(strcmp(recvBuff, "fin") == 0){
					send(s, "Confirmacion de fin", sizeof(sendBuff), 0);
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout<<"el ganador es : "<<recvBuff<<endl;
					loggerFile << "Ganador establecido: " << recvBuff << "\n";
					final=!final;
					break;	
				}else{
					cout<<recvBuff<<endl;
					
					send(s, "Confirmacion", sizeof(sendBuff), 0);
					loggerFile << "Enviada confirmacion: " << recvBuff <<"\n";
				}
				
				
			}
		}
			

	}

	loggerFile << "Final\n";
	loggerFile.close();


	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}
