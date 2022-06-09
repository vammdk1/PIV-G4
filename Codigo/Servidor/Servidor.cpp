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
	std::ofstream loggerFile;
	loggerFile.open("../Archivos/ServerLogger.txt");
    
	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];
	

	cout<<"\nInitialising Winsock..."<<endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout<<"Failed. Error Code : "<< WSAGetLastError()<<endl;
		return -1;
	}

	cout<<"Initialised."<<endl;

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout<<"Could not create socket : "<< WSAGetLastError()<<endl;
		WSACleanup();
		return -1;
	}

	cout<<"Socket created"<<endl;

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		cout<<"Bind failed with error code: "<< WSAGetLastError()<<endl;
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	cout<<"Bind done"<<endl;

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		cout<<"Listen failed with error code: "<< WSAGetLastError()<<endl;
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	cout<<"Waiting for incoming connections..."<<endl;
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		cout<<"accept failed with error code : "<< WSAGetLastError()<<endl;
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	cout<<"Incomming connection from: "<< inet_ntoa(client.sin_addr) << ntohs(client.sin_port)<<endl;

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);
	loggerFile << "Servidor iniciado\n";
	loggerFile.close();
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
		cout<<"recibiendo numero de jugadores "<<endl;
		cout<<"jugadores recibidos: " <<recvBuff <<endl;
		sscanf(recvBuff, "%i",&Njugadores);//asignar numero de jugadores
		//loggerFile << "Jugadores recividos: \n";
		Jugador* listaJ[Njugadores];
		//Carta listaC[Njugadores];
		cout<<Njugadores<<endl;
		for(int i = 0;i<Njugadores;i++){
			strcpy(sendBuff,  "Nombre del jugador");
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
			cout<<"pregunta enviada: "<< sendBuff<<endl;
			do {
				int fase1 = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
				if (bytes > 0) {
					cout<<"Recibiendo nombre " <<i<<endl;
					cout<<"Data received: "<< recvBuff<<endl;
					
					//crear jugador	
					listaJ[i] = new Jugador(recvBuff);
					char temp[3];
					lastPlayer++;

					listaJ[i]->setID(lastPlayer);
					sprintf(temp, "%i", lastPlayer);	
					insertNewPlayerData(db, recvBuff, temp); //Jugador insertado en la base de datos		
					if(posRey == i){
						listaJ[i]->cambiarRey();
					} 
					//asignar cartas
					for(int x = 0; x<7; x++){
				
						char tempWhiteCard[100];
						char tempIDwc[4];
						
						sprintf(tempIDwc, "%i", currentWhiteCard);
						
						strcpy(tempWhiteCard, selectWhiteCard(db, tempIDwc));
						currentWhiteCard = ((currentWhiteCard + 1) % maxWhiteCard);
						if(currentWhiteCard == 0){
							currentWhiteCard++;
						}
						
						
						Carta* carta = new Carta();
						
						setTexto(carta, tempWhiteCard);
						carta->id = 0;
						carta->negra = 0;
						
						listaJ[i]->cambiarCarta(carta, x);
						
					
					}
					loggerFile.open("../Archivos/ServerLogger.txt", std::ios_base::app);
					loggerFile << "Jugador creado\n";
					loggerFile.close();
					break;
					}
			} while (1);
			//printf("%i \n",Njugadores);
			//ver como mandar imágenes, usar control por mensaje
		}
		//loggerFile << "Inicio F2\n";
		strcpy(sendBuff,"inicio F2");
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);//cambiar mensaje en cliente
		cout<<"cambio a fase 2"<<endl;
		do {
			char listaRespuestas[Njugadores][100];
			char tempBlackCard[100];
			char tempIDbc[4];
			sprintf(tempIDbc, "%i", currentBlacCard);
			strcpy(tempBlackCard, selectBlackCard(db, tempIDbc));
			currentBlacCard = ((currentBlacCard + 1) % maxBlackCard);
			if(currentBlacCard == 0){
				currentBlacCard++;
			}
			for(int i = 0; i<Njugadores;i++){
				if(true){
					strcpy(sendBuff,listaJ[i]->getNombre());
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
					do {
						int JugadoR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
						if (bytes > 0) {
								cout<<recvBuff<<endl;//Jugador r confirmado
								break;
							}
					} while (1);
					//fase de envio de 7 cartas seguidas
					for(int x =0; x<8;x++){
						//enviar carta
						if(x == 7){
							strcpy(sendBuff,tempBlackCard);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
							cout<<"pregunta enviada: "<< sendBuff <<endl;
							do {
								int CartaR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
									if (bytes > 0) {
											cout<<recvBuff<<endl;//carta r confirmado
											break;
									}
							} while (1);
						} else {
							strcpy(sendBuff, listaJ[i]->seleccionarCarta(x).texto);
							send(comm_socket,sendBuff, sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
							cout<<"pregunta enviada: "<< sendBuff <<endl;
							do {
								int CartaR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
									if (bytes > 0) {
											cout<< recvBuff<<endl;//carta r confirmado
											break;
									}
							} while (1);
						}
						
					}
					loggerFile.open("../Archivos/ServerLogger.txt", std::ios_base::app);
					loggerFile << "Cartas Enviadas\n";
					loggerFile.close();
					//fase de respuesta de ronda de jugadorx
					strcpy(sendBuff, "Que carta elijes? :");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
					cout<<"pregunta por carta: "<<sendBuff<<endl;
					do {
						cout << "LLEGO" << endl;
						int SeleccionR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
						if (bytes > 0) {
							cout<< recvBuff<<endl;//Jugador r confirmado
							int temp0=0;
							sscanf(recvBuff,"%i", &temp0);
							strcpy(listaRespuestas[i], listaJ[i]->seleccionarCarta(temp0 - 1).texto);
							//agregar en la lista de cartas la carta en la pos temp0
							//Cambiar la carta
							char tempWhiteCard2[100];
							char tempIDwc2[4];
							
							sprintf(tempIDwc2, "%i", currentWhiteCard);
							
							strcpy(tempWhiteCard2, selectWhiteCard(db, tempIDwc2));
							currentWhiteCard = ((currentWhiteCard + 1) % maxWhiteCard);
							if(currentWhiteCard == 0){
								currentWhiteCard++;
							}
							
							
							Carta* carta = new Carta();
							
							setTexto(carta, tempWhiteCard2);
							carta->id = 0;
							carta->negra = 0;
							
							listaJ[i]->cambiarCarta(carta, temp0 -1);
							loggerFile.open("../Archivos/ServerLogger.txt", std::ios_base::app);
							loggerFile << "Carta elegida\n";
							loggerFile.close();
							break;
						}

					} while (1);
					
				}
			}
			strcpy(sendBuff, "Rey");
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
			do {
				//fase de envio de 8 cartas de respuesta
				for(int x =0; x<Njugadores;x++){
					//enviar carta
					strcpy(sendBuff, listaRespuestas[x]);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
					cout<<"pregunta enviada: "<< sendBuff<<endl;
					do {
						int ReyR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
							if (ReyR > 0) {
									cout<<recvBuff<<endl;//carta r confirmado
									break;
							}
					} while (1);
				
				} 
				strcpy(sendBuff, "Que carta gana? :");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);//esta frase activa fase 1 en cliente
				cout<<"pregunta por carta:  "<< sendBuff<<endl;
				do {
					int SelecciopnReyR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
					if (SelecciopnReyR > 0) {
						cout<<recvBuff<<endl;//Jugador r confirmado
						int temp1=0;
						//scanf(recvBuff,"%i",temp1);
						//agregar al jugador temp1 un punto
						listaJ[temp1]->sumarPuntos(1);
						loggerFile.open("../Archivos/ServerLogger.txt", std::ios_base::app);
						loggerFile << "Carta rey elegida\n";
						loggerFile.close();
						break;
					}

				} while (1);
				cout<<"cambio de rey"<<endl;
				//desacivar rey
				listaJ[posRey]->cambiarRey();
				posRey = (posRey + 1) % Njugadores;
				listaJ[posRey]->cambiarRey();
				//activar siguiente rey
				for(int i =0; i<Njugadores;i++){//comprobación del ganador
					if(listaJ[i]->getPuntos() == Njugadores){
						// un jugador tiene el mismo numero de puntos que numero de jugadores 
						strcpy(sendBuff, "fin");
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);//cambiar mensaje en cliente
						do {
						int FinR = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//pregunta si hay mensajes
							if (FinR > 0) {
									cout<<recvBuff<<endl;//fin r confirmado
									strcpy(sendBuff,listaJ[i]->getNombre());
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);//cambiar mensaje en cliente
									JuegoFin=!JuegoFin;
									char gameID[3];
									lastGame++;
									sprintf(gameID, "%i", lastGame);
									char playerID[3];
									sprintf(playerID, "%i", listaJ[i]->getID());
									insertNewGameData(db, gameID, playerID);
									break;
							}
						} while (1);
						cout<<"-------------------------------------------"<<endl;
						break;
					}
				}
				cout<<"cambio de ronda"<<endl;
			//	send(comm_socket, "inicio F2", sizeof(sendBuff), 0);//cambiar mensaje en cliente
				break;
					

			} while(1);
		
			cout<<"1"<<endl;
			if (strcmp(recvBuff, "Confirmacion de fin") == 0){
				break;
			}
		}while (1);

		cout<<"2"<<endl;
		if (strcmp(recvBuff, "Confirmacion de fin") == 0){
			break;
		}
	}
}while(!JuegoFin);

	loggerFile.open("../Archivos/ServerLogger.txt", std::ios_base::app);
	loggerFile << "Final\n";
	loggerFile.close();
	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();


	return 0;
}