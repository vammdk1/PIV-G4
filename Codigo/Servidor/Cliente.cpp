// IMPORTANT: Winsock Library ("ws2_32") should be linked
extern "C"{
    #include <stdio.h>
    #include <winsock2.h>
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

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
        cout << line << endl;
    }
    myfile.close();
    

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

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

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	// SEND and RECEIVE data
	printf("Sending message 1... \n");
	strcpy(sendBuff, "Hello, server.");
	send(s, sendBuff, sizeof(sendBuff), 0);

	printf("Receiving message 1... \n");
	recv(s, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: %s \n", recvBuff);

	printf("Sending message 2... \n");
	strcpy(sendBuff, "Hello again.");
	send(s, sendBuff, sizeof(sendBuff), 0);
	printf("Data sent: %s \n", sendBuff);

	printf("Receiving message 2... \n");
	recv(s, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: %s \n", recvBuff);

	printf("Sending last message... \n");
	strcpy(sendBuff, "Bye");
	send(s, sendBuff, sizeof(sendBuff), 0);
	printf("Data sent: %s \n", sendBuff);

	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}
