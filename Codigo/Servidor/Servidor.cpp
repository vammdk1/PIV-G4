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
#include <string>
#include <stdlib.h>
#include "../Estructuras/jugador.h"

using namespace std;


// IMPORTANT: Winsock Library ("ws2_32") should be linked



int main(int argc, char *argv[]) {

	
	char* SERVER_IP;
    int SERVER_PORT = 6000;
    std::ifstream myfile;
    myfile.open("../Archivos/.config");
	sqlite3* db;
	sqlite3_open("../Archivos/database.db", &db);
    
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
	
	char str[50];
	int Njugadores = 0;
	int posRey=0;
	int currentWhiteCard = 1;
	int currentBlacCard = 1;
	int maxBlackCard = 0;
	int maxWhiteCard = 0;
	int lastPlayer = 0;
	int lastGame = 0;
	sscanf(getLastBlackCardID(db), "%i", &maxBlackCard);
	sscanf(getLastWhiteCardID(db), "%i", &maxWhiteCard);
	sscanf(getLastPlayerID(db), "%i", &lastPlayer);
	sscanf(getLastGameID(db), "%i", &lastGame);
	bool JuegoFin=false;


do{
	int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	if (bytes > 0) {
		//fase1 seleccionar jugadores
		printf("recibiendo numero de jugadores \n");
		printf("jugadores recibidos: %s \n", recvBuff);
		sscanf(recvBuff, "%i",&Njugadores);//asignar numero de jugadores
		Jugador listaJ[Njugadores];
		Carta listaC[Njugadores];
		printf("%i \n",Njugadores);
		for(int i = 0;i<Njugadores;i++){
			send(comm_socket, "Nombre del jugador", sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
			printf("pregunta enviada: %s \n", sendBuff);
			do {
				int fase1 = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
				if (bytes > 0) {
					printf("Recibiendo nombre %i \n",i);
					printf("Data received: %s \n", recvBuff);	
					//crear jugador				
					//if(posRey= i) jugador.rey=true;
					//asignar cartas
					break;
					}
			} while (1);
			//printf("%i \n",Njugadores);
			//ver como mandar imágenes, usar control por mensaje
		}
			
		send(comm_socket, "inicio F2", sizeof(sendBuff), 0);//cambiar mensaje en cliente
		printf("cambio a fase 2\n");
		do {
			for(int i =0; i<Njugadores;i++){
				if(true){
					send(comm_socket, "jugador [x]", sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
					do {
						int JugadoR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
						if (bytes > 0) {
								printf(" %s \n", recvBuff);//Jugador r confirmado
								break;
							}
					} while (1);
					//fase de envio de 7 cartas seguidas
					for(int x =0; x<8;x++){
						//enviar carta
						send(comm_socket, "carta", sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
						printf("pregunta enviada: %s \n", sendBuff);
						do {
							int CartaR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
								if (bytes > 0) {
										printf(" %s \n", recvBuff);//carta r confirmado
										break;
								}
						} while (1);
					}
					//fase de respuesta de ronda de jugadorx
					send(comm_socket, "Que carta elijes? :", sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
					printf("pregunta por carta: %s \n", sendBuff);
					do {
						int SeleccionR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
						if (bytes > 0) {
							printf(" %s \n", recvBuff);//Jugador r confirmado
							int temp0=0;
							//scanf(recvBuff,"%i",temp0);
							//agregar en la lista de cartas la carta en la pos temp0
							break;
						}

					} while (1);
				}
			}
			send(comm_socket, "Rey", sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
			do {
				//fase de envio de 8 cartas de respuesta
				for(int x =0; x<8;x++){
					//enviar carta
					send(comm_socket, "carta del rey", sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
					printf("pregunta enviada: %s \n", sendBuff);
					do {
						int ReyR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
							if (ReyR > 0) {
									printf(" %s \n", recvBuff);//carta r confirmado
									break;
							}
					} while (1);
				
				} 
				send(comm_socket, "Que carta gana? :", sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
				printf("pregunta por carta: %s \n", sendBuff);
				do {
					int SelecciopnReyR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
					if (SelecciopnReyR > 0) {
						printf(" %s \n", recvBuff);//Jugador r confirmado
						int temp1=0;
						//scanf(recvBuff,"%i",temp1);
						//agregar al jugador temp1 un punto
						break;
					}

				} while (1);
				printf("cambio de rey\n");
				//desacivar rey
				posRey++;
				//activar siguiente rey
				for(int i =0; i<Njugadores;i++){//comprobación del ganador
					if(false){
						// un jugador tiene el mismo numero de puntos que numero de jugadores 
						send(comm_socket, "fin", sizeof(sendBuff), 0);//cambiar mensaje en cliente
						do {
						int FinR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
							if (FinR > 0) {
									printf(" %s \n", recvBuff);//fin r confirmado
									send(comm_socket, "Ganador X", sizeof(sendBuff), 0);//cambiar mensaje en cliente
									JuegoFin=!JuegoFin;
									break;
							}
						} while (1);
						printf("-------------------------------------------\n");
						break;
					}
				}
				printf("cambio de ronda");
				send(comm_socket, "inicio F2", sizeof(sendBuff), 0);//cambiar mensaje en cliente
				break;
					

			} while(1);
		
			printf("1\n");
			if (strcmp(recvBuff, "Confirmacion de fin") == 0){
				break;
			}
		}while (1);

		printf("2\n");
		if (strcmp(recvBuff, "Confirmacion de fin") == 0){
			break;
		}
	}
}while(!JuegoFin);


	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}