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

	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	wsastartup = WSAStartup(wVersionRequested, &wsaData);
	if (wsastartup != NO_ERROR) cout << "Errore WSAStartup()\n" << endl;

	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket < 0) cout << "Server: errore nella creazione della socket.\n" << endl;
	else cout << "La Listening Socket è partita\n" << endl;

	port = 27000;

	Server_addr.sin_family = AF_INET;
	Server_addr.sin_addr.s_addr = 0;
	Server_addr.sin_port = htons(port);

	if (bind(listenSocket, (LPSOCKADDR)&Server_addr, sizeof(struct sockaddr)) < 0)
		cout << "Server: errore durante la bind.\n" << endl;

	ls_result = listen(listenSocket, SOMAXCONN);
	if (ls_result < 0) printf("Server: errore durante la listen.\n");
	else cout << "La Socket è in Ascolto\n" << endl;

	sin_size = sizeof(struct sockaddr_in);
	remoteSocket = accept(listenSocket, (struct sockaddr *)&Client_addr, &sin_size);

	cout << "client " << inet_ntoa(Client_addr.sin_addr) << "  " << ntohs(Client_addr.sin_port) << endl;
	cout << "server " << inet_ntoa(Server_addr.sin_addr) << " " << ntohs(Server_addr.sin_port) << endl;
	chatting( listenSocket);

	cout << "Chiudo il Server" << endl;
	closesocket(remoteSocket);
	WSACleanup();
	return 0;
}

