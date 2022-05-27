extern "C"{
    #include <stdio.h>
    #include <winsock2.h>
	#include "../DataBase/DataBase.h" //link la shell.c
	#include "../Estructuras/carta.h"
    
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include "../Estructuras/jugador.h"

using namespace std;


// IMPORTANT: Winsock Library ("ws2_32") should be linked


int main(int argc, char *argv[]) {

	char* SERVER_IP;
    int SERVER_PORT = 6000;
    std::ifstream myfile;
    myfile.open("../../Archivos/.config");
    
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
        
    }
    myfile.close();
	cout << SERVER_IP << endl;
	cout << SERVER_PORT << endl;
    
	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];
	

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n");

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);
	
	//gameLogic;
	bool gameFinished = false;
	char str[50];
	int Njugadores,Nrondas;
	
	//SEND and RECEIVE data	//Inicio del juego
	printf("Inicio\n");
	int i =1;
	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//1b
	printf("paso %i \n",i);
	i++;
	sscanf(recvBuff, "%i",&Njugadores );
	printf("NJugadores : %i \n", Njugadores);
	
	int x = 0;
	
	Jugador listaJ[Njugadores];
	// esta usando el tamaño de un caracter
	
	while (x<Njugadores)
	{
		
		send(comm_socket, "Introduce los datos del jugador", sizeof(sendBuff), 0);//2a
		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		if (bytes > 0) {
			printf("Nombre %s, pos: %i\n", recvBuff,x);
			listaJ[x] = *(new Jugador(recvBuff));//asignar 7 cartas
			x++;
		}
		strcpy(recvBuff," ");
	}
	printf(listaJ[0].getNombre());

	//Inicio del juego
bool FinJuego=false;
int TurnoRey=0;
int PosRey;
int RespuestaCarta;
Carta ListaRespuestas[Njugadores];
	while (!FinJuego)
	{
		listaJ[TurnoRey].cambiarRey();	
		TurnoRey++;
		//sacar carta negra de la base datos
		send(comm_socket, "carta de la ronda", sizeof(sendBuff), 0);
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		printf("Data received: %s ", recvBuff);
		//sacar carta de cada jugador
		for (int i = 0; i < Njugadores; i++)
		{
			
			if(listaJ[i].esRey()){
				PosRey=i;
			}else{
				int ContadorCartas=0;
				//Mandar nombre del jugador
				send(comm_socket, listaJ[i].getNombre(), sizeof(sendBuff), 0);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				printf("Data received: %s ", recvBuff);
				do
				{
					send(comm_socket, listaJ[i].seleccionarCarta(ContadorCartas), sizeof(sendBuff), 0);
					ContadorCartas++;
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					printf("Data received: %s ", recvBuff);
				} while (strcmp(recvBuff,"carta7"));
				//pregunta por respuesta de ronda
				send(comm_socket, "Selecciona una carta: ", sizeof(sendBuff), 0);
				//recibir respuesta de ronda
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				sscanf(recvBuff, "%i",&RespuestaCarta);
				ListaRespuestas[i]=listaJ[i].seleccionarCarta(RespuestaCarta);
				if(listaJ[i].getPuntuacion()>=Njugadores){
					FinJuego = true;
				}			
			}	
		}
		//turno del rey 
		//envio de carta negra 
		send(comm_socket, "carta", sizeof(sendBuff), 0);
		//rececpcion de respuesta
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		printf("Data received: %s ", recvBuff);
		
		for (int x = 0; x < Njugadores; x++)
		{
			if(x!=PosRey){
			send(comm_socket, ListaRespuestas[x], sizeof(sendBuff), 0);
			//rececpcion de respuesta
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			printf("Data received: %s ", recvBuff);
			}
		}		

		listaJ[TurnoRey-1].cambiarRey();
	}
	

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}