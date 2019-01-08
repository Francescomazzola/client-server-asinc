#include <iostream>
#include <stdio.h>
#include <winsock.h>
#include <string.h>
#pragma comment (lib,"Ws2_32.lib")

using namespace std;
SOCKET	clientsocket;
SOCKADDR_IN addr;

void chatting() {
	char messaggio[80];
	char buffer[1024] = { 0 };

	cout << "dammi il messaggio da fornire al server, per chiudere premere q" << endl;
	cin >> messaggio;
	send(clientsocket, messaggio, sizeof(messaggio), 0);
	if (strcmp(messaggio,"q")==0)
		return;
	if (recv(clientsocket, buffer, 2000, 0) > 0) {
		cout << buffer << endl;
	}
	chatting();

}

int main()
{
	int valread;
	short port;
	char ip[15];
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(wVersionRequested, &wsaData);
	port = 27000;
	addr.sin_family = AF_INET;
	cout << "dammi l'ip" << endl;
	gets_s(ip);
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(clientsocket, (LPSOCKADDR)&addr, sizeof(addr)) < 0) {
		cout << "errore!" << endl;
		exit(1);
	}
	chatting();
	closesocket(clientsocket);
	WSACleanup();
	

}

