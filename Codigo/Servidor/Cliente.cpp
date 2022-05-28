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
	printf("+------------------------------------+\n|+----------------------------------+|\n");
	printf("||                                  ||\n");
	printf("||     CMD CONTRA LA HUMANIDAD      ||\n");
	printf("||                                  ||\n");
	printf("++----------------------------------++\n++----------------------------------++\n");
}
void LineaJugador(Jugador* nombres[], int longitud){
	for(int i=0;i<longitud;i++){
		if(nombres[i]->esRey){
			printf("|| %s |     %i     |     *     ||\n",nombres[i]->getNombre(),nombres[i]->getPuntos);
		}else{
			printf("|| %s |     %i     |           ||\n",nombres[i]->getNombre(),nombres[i]->getPuntos);
		}
		
	}
	
	}

void LineaConsola(){
	printf("++-----------+----------+-----------++\n|| Jugadores | Puntos   |   Rey     ||\n--------------------------------------\n");
}

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
        //out << line << endl;
    }
    myfile.close();
    

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];
	char str[50];

	//printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	//printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	//printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	//printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
	//ntohs(server.sin_port));

	//Fase 1
	cabecera();
	printf("Introduce el numero de jugadores: ");
	fgets(str, 2, stdin);
	fflush(stdin);
	strcpy(sendBuff, str);
	send(s, sendBuff, sizeof(sendBuff), 0); //1a

	int NJ ;
	sscanf(str, "%i",&NJ);
	//Fase 2 
	int i =0;
	Jugador* listaJ[NJ]={};
	while (i<NJ)
	{
		//printf("Receiving message 2... \n");
		recv(s, recvBuff, sizeof(recvBuff), 0);
		printf(" %s ", recvBuff);
		printf("%i \n",i+1);
		fgets(str, 10, stdin);
		fflush(stdin);
		strcpy(sendBuff, str);
		(listaJ[i]) = (new Jugador(str));
		send(s, sendBuff, sizeof(sendBuff), 0);
		i++;
	}

	cabecera();
	LineaConsola();
	LineaJugador(listaJ, NJ);

	//Fase 3
	bool FinJuego=false;
	int TurnoRey=0;

	while (!FinJuego)
	{
		(listaJ[TurnoRey])->getNombre();	
		printf("Ronda %i \n",TurnoRey+1);
		//recibir carta negra , equivalente en la linea 161 de serviddor
			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("Data received: %s \n", recvBuff);
			//responder receipción de la carta negra
			send(s, "Carta negra recibida", sizeof(sendBuff), 0);
		for (int x = 0; x < NJ; x++)
		{
			if((listaJ[x])->getPuntos()==NJ){
				FinJuego = true;
				break;
			//enviar fin del juego
			}else if(x==TurnoRey){
				printf("este es el jugador rey, pasar al siguiente\n");
			}else{
				//recibir Nombre del jugador x
				recv(s, recvBuff, sizeof(recvBuff), 0);
				printf("Turno de: %s \n", recvBuff);
				//responder receipción de nombre
				send(s, recvBuff, sizeof(sendBuff), 0);
				for (int i = 0; i < 7; i++)
				{
					//recibir carta blanca
					recv(s, recvBuff, sizeof(recvBuff), 0);
					printf("%s \n", recvBuff);
					//enviar confirmacion de carta
					send(s, "Carta blanca ", sizeof(sendBuff), 0);
					
				}
				//recibir pregunta por carta de la ronda
				recv(s, recvBuff, sizeof(recvBuff), 0);
				printf(recvBuff);
				//responder el numero de la carta que será la respuesta
				fgets(str, 2, stdin);
				fflush(stdin);
				send(s, str, sizeof(sendBuff), 0);
				//cambio de jugador, el rey siempre es el ultimo y se hace afuera del bucle
			}
		}

		//recibir la carta negra de la ronda para el rey
		recv(s, recvBuff, sizeof(recvBuff), 0);
		printf("%s \n", recvBuff);
		//responder receipción de la carta negra
		send(s, "Carta negra recibida", sizeof(sendBuff), 0);
		for (int i = 0; i < NJ; i++) //equivalente en linea 195 servidor
		{
			if(i!=TurnoRey){			
				//recibir las respuestas de los otros jugadores
				recv(s, recvBuff, sizeof(recvBuff), 0);
				printf("%i - %s \n", i+1 ,recvBuff);
				//Responder recepción de la carta
				send(s, "Carta blaca recibida", sizeof(sendBuff), 0);
			}
		}
		//recibir pregunta del servidor por la mejor carta
		recv(s, recvBuff, sizeof(recvBuff), 0);
		printf("%s \n", recvBuff);
		//responder pregunta
		fgets(str, 2, stdin);
		fflush(stdin);
		send(s, str, sizeof(sendBuff), 0);
		//recibir puntuación actualizada
		for (int i = 0; i < NJ; i++) 
		{
			//recibir la puntuación del jugador x
			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s \n" ,recvBuff);
			int PuntosNuevos;
			sscanf(recvBuff,"%i", &PuntosNuevos);
			(listaJ[i])->setPuntos(PuntosNuevos);
			//Responder recepción de la carta
			send(s, "Puntuación actualizada", sizeof(sendBuff), 0);
		}
		cabecera();
		LineaConsola();
		LineaJugador(listaJ, NJ);
		TurnoRey = (TurnoRey + 1) % NJ;
	}




	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}
