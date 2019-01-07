#include <stdio.h>
#include <winsock.h>
#include <string.h>
#include <iostream>
#pragma comment (lib,"Ws2_32.lib")


using namespace std;
SOCKET	remoteSocket;
SOCKADDR_IN Client_addr;
int ls_result;
int sin_size;

void chatting(SOCKET	listenSocket) {
	char buffer[256];
	
	sin_size = sizeof(struct sockaddr_in);
	remoteSocket = accept(listenSocket, (struct sockaddr *)&Client_addr, &sin_size);

	/* Il Server accetta il messaggio dal Client */
	recv(remoteSocket, buffer, sizeof(buffer), 0);
	if (strcmp(buffer, "q") == 0)
		return;
	cout << "messaggio arrivato:" << buffer << endl;
	char ok[256];
	cin >> ok;
	send(remoteSocket, ok, strlen(ok), 0);
	chatting(listenSocket);
}

int main()
{
	SOCKET	listenSocket;
	SOCKADDR_IN Server_addr;
	short port;
	int wsastartup;
	

	/* Inizializzazione della libreria Socket */
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	wsastartup = WSAStartup(wVersionRequested, &wsaData);
	if (wsastartup != NO_ERROR) printf("Errore WSAStartup()\n");

	/* Creazione della Socket che si porrà in ascolto di richieste del Client*/
	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket < 0)
		printf("Server: errore nella creazione della socket.\n");
	else printf("La Listening Socket è partita\n");

	/* Effettua la bind sull’indirizzo e porta ora specificati */
	port = 3456;

	Server_addr.sin_family = AF_INET;
	Server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	Server_addr.sin_port = htons(port);

	if (bind(listenSocket, (LPSOCKADDR)&Server_addr, sizeof(struct sockaddr)) < 0)
		printf("Server: errore durante la bind.\n");

	/* La socket si pone in "ascolto" tramite la listen() */
	ls_result = listen(listenSocket, SOMAXCONN);
	if (ls_result < 0) printf("Server: errore durante la listen.\n");
	else printf("La Socket è in Ascolto\n");

	chatting( listenSocket);

	printf("Chiudo il Server");
	closesocket(remoteSocket);
	WSACleanup();
	system("pause");
	return 0;
}

