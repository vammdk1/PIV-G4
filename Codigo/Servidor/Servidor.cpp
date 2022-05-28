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
	int Njugadores,Nrondas;
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
	
	//SEND and RECEIVE data	//Inicio del juego
	printf("Inicio\n");
	int i =1;
	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);//1b
	printf("paso %i \n",i);
	i++;
	sscanf(recvBuff, "%i",&Njugadores );
	printf("NJugadores : %i \n", Njugadores);
	if(Njugadores < 4){
		Njugadores = 4;
	}
	int x = 0;
	
	Jugador* listaJ[Njugadores]={};
	// esta usando el tamaño de un caracter
	
	while (x<Njugadores)
	{
		send(comm_socket, "Introduce los datos del jugador", sizeof(sendBuff), 0);//2a
		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		if (bytes > 0) {
			printf("Nombre %s, pos: %i\n", recvBuff,x);
			(listaJ[x]) = (new Jugador(recvBuff));//problemas si hay entre 5 y 6 jugadores
			char temp[3];
			lastPlayer++;
	
			listaJ[x]->setID(lastPlayer);

			sprintf(temp, "%i", lastPlayer);
			
			insertNewPlayerData(db, recvBuff, temp);
			for(int i = 0; i<7; i++){
				
				char tempWhiteCard[100];
				char tempIDwc[4];
				
				sprintf(tempIDwc, "%i", currentWhiteCard);
				
				strcpy(tempWhiteCard, selectWhiteCard(db, tempIDwc));
				currentWhiteCard = ((currentWhiteCard + 1) % maxWhiteCard) + 1;
				
				Carta* carta = new Carta();
				
				setTexto(carta, tempWhiteCard);
				carta->id = 0;
				carta->negra = 0;
				
				listaJ[x]->cambiarCarta(carta, i);
				
			
			}
			
			
			x++;
		}
		strcpy(recvBuff," ");
	}
	printf("Primer nombre de la lista: %s\n",(listaJ[0])->getNombre());

	
bool FinJuego=false;
int TurnoRey=0;
int RespuestaCarta;
char ListaRespuestas[Njugadores][100];

//Fase 3
while (!FinJuego)
{
	(listaJ[TurnoRey])->getNombre();	
	printf("Ronda %i \n",TurnoRey+1);
	
	//sacar carta negra de la base datos
	char tempBlackCard[100];
	char tempIDbc[4];
	sprintf(tempIDbc, "%i", currentBlacCard);
	strcpy(tempBlackCard, selectBlackCard(db, tempIDbc));
	currentBlacCard = ((currentBlacCard + 1) % maxBlackCard) + 1;
	//Enviar
	
	send(comm_socket, tempBlackCard, sizeof(sendBuff), 0);
	cout << "" << endl;
	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Respuesta : %s \n", recvBuff);
	//sacar carta de cada jugador
	for (int i = 0; i < Njugadores; i++)
	{
		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		if(bytes > 0){
			cout << "Entro el server" << endl;
			if((listaJ[i])->getPuntos()==Njugadores){
				FinJuego = true;
				/*char* tempG;
				lastGame++;
				sprintf(tempG, "%i", lastGame);
				string tempST = std::to_string(listaJ[i]->getID());
				char* tempI;
				strcpy(tempI, tempST);
				//sprintf(tempI, "%i",  listaJ[i]->getID());
				insertNewGameData(db, lastGame, tempI);*/
				break;
				//enviar fin del juego
			}else if(i==TurnoRey){
				printf("El rey es %s \n",(listaJ[i])->getNombre());
				
			}else{
				//Mandar nombre del jugador
				cout << "Entro al else"<< endl;
				send(comm_socket, (listaJ[i])->getNombre(), sizeof(sendBuff), 0);
				cout << "ENVIO" << endl;
				//recibir confirmacion del nombre
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				printf("El nombre del jugador de turno es: %s \n", recvBuff);
				for (int x = 0; x < 7; x++)
				{
					
					//envio de carta blanca
					//Enviar del array del Jugador
					send(comm_socket, (listaJ[i]->seleccionarCarta(x)).texto, sizeof(sendBuff), 0);
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					printf("%s%i devuelta del cliente\n", recvBuff,x);
				}
				//pregunta por respuesta de ronda
				send(comm_socket, "Selecciona una carta: ", sizeof(sendBuff), 0);
				//recibir numero de la carta de esta ronda
				
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				
				
				sscanf(recvBuff, "%i",&RespuestaCarta);
				

				/*char tempWhiteCard2[100];
				char tempIDwc2[4];
				sprintf(tempIDwc2, "%i", currentWhiteCard);
				strcpy(tempWhiteCard2, selectWhiteCard(db, tempIDwc2));
				currentWhiteCard = ((currentWhiteCard + 1) % maxWhiteCard) + 1;
				*///Carta* carta2 = new Carta();

				//ListaRespuestas[i]=listaJ[i].seleccionarCarta(RespuestaCarta).texto;
				strcpy(ListaRespuestas[i], listaJ[i]->seleccionarCarta(RespuestaCarta-1).texto);
				//setTexto((listaJ[i]->seleccionarCarta(RespuestaCarta-1)), tempWhiteCard2);	
				//strcpy((listaJ[i]->seleccionarCarta(RespuestaCarta-1).texto), tempWhiteCard2);
			}	
		}
		
	}
	//turno del rey 
	//envio de carta negra 
	send(comm_socket, tempBlackCard, sizeof(sendBuff), 0);
	//rececpcion de respuesta
	printf("=================================================\n");
	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: %s \n", recvBuff);
	//Envio de las cartas blancas
	for (int x = 0; x < Njugadores; x++)
	{
		if(x!=TurnoRey){
			send(comm_socket, ListaRespuestas[x], sizeof(sendBuff), 0);
			//rececpcion de respuesta
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			printf("%s \n", recvBuff);
		}
	}	
	//enviar pregunta de ganador 	
	send(comm_socket, "Que carta es la mejor ?", sizeof(sendBuff), 0);
	//recibir respuesta 
	int RespuestaPunto;
	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Respuesta: %s \n", recvBuff);
	sscanf(recvBuff,"%i", &RespuestaPunto);
	
	(listaJ[RespuestaPunto-1])->sumarPuntos(1);
	
	//enviar infomación actualizada de cada jugador
	for (int x = 0; x < Njugadores; x++)
	{
		int c= ((listaJ[x])->getPuntos());
		string tempS = to_string(c);
		char const* temp = tempS.c_str();
		//scanf( listaJ[x]->getPuntos(),"%s",&temp);
		send(comm_socket, temp , sizeof(sendBuff), 0);
		//rececpcion de respuesta
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		printf("Data received: %s \n", recvBuff);
		
	}	
	TurnoRey = (TurnoRey + 1) % Njugadores;

}

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}