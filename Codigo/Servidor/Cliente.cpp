// IMPORTANT: Winsock Library ("ws2_32") should be linked
extern "C"{
    #include <stdio.h>
    #include <winsock2.h>
	#include <stdlib.h>
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


char* controlador(int min, int max,string mensaje, string error,char* resp){
	while (1)
	{
		cout<<mensaje;
		cin>>resp;
		int temp;
		sscanf(resp, "%i", &temp);
		if(temp>=min&&temp<max){
			break;
		}else{
			cout<<error<<endl;
		}
	}
	return resp;

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
	cabecera();

	controlador(4,9,"Introduce el numero de jugadores: ","Solo se adminten de entre 4 y 9 jugadores",str);
	strcpy(sendBuff, str);
	send(s, sendBuff, sizeof(sendBuff), 0); //1a
	loggerFile << "Numero de jugadores: " << str << "\n";
	bool final=false;
	int NJ  = stoi(str);
	int cont=1;
	bool control=false;
	while(!final){
		//fase1
		recv(s, recvBuff, sizeof(recvBuff), 0);
		if(strcmp(recvBuff, "Nombre del jugador") == 0){
			system ("CLS");
			loggerFile << "Introducir jugador \n";
			cout<<"Introduce el nombre del jugador "<<cont<<": "<<endl;
			cin>>str;		
			strcpy(sendBuff, str);
			send(s, sendBuff, sizeof(sendBuff), 0);
			cont++;
		}else if(strcmp(recvBuff, "inicio F2") == 0){
			loggerFile << "Inicio Fase 2\n";
			system ("CLS");
			while(true){
				recv(s, recvBuff, sizeof(recvBuff), 0);
				if(strcmp(recvBuff, "Que carta elijes? :") == 0){
					controlador(1,8,recvBuff,"Ingresa un numero entre 1 y 7 ambos incluidos",str);
					strcpy(sendBuff, str);
					send(s, sendBuff, sizeof(sendBuff), 0);
					loggerFile << "Eleccion de carta: " << sendBuff << "\n";
					system ("CLS");
				}else if(strcmp(recvBuff, "Rey") == 0){
					do
					{
						recv(s, recvBuff, sizeof(recvBuff), 0);
						if(strcmp(recvBuff, "Que carta gana? :") == 0){
							controlador(1,NJ,recvBuff,"Ingresa un numero entre 1 y el numero de juygadores, ambos incluidos",str);
							strcpy(sendBuff, str);
							send(s, sendBuff, sizeof(sendBuff), 0);
							loggerFile << "Eleccion de carta: " << sendBuff << "\n";
							system ("CLS");
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
