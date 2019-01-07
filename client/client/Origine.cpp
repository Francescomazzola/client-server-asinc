#include <iostream>
#include <stdio.h>
#include <winsock.h>
#include <string.h>
#pragma comment (lib,"Ws2_32.lib")

using namespace std;

int main()
{
	int valread;
	SOCKET	clientsocket;
	SOCKADDR_IN addr;
	char messaggio[80];
	short port;
	char buffer[1024] = {0};
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(wVersionRequested, &wsaData);
	port = 3456;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(port);
	clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (connect(clientsocket, (LPSOCKADDR)&addr, sizeof(addr)) < 0) {
		cout << "errore!" << endl;
		exit(1);
	}
		
	cout << "dammi il messaggio da fornire al server, per chiudere premere q" << endl;
	cin >> messaggio;
	send(clientsocket, messaggio, sizeof(messaggio), 0);
	if (messaggio == "q")
		exit(1);
	if (recv(clientsocket, buffer, 2000, 0) > 0) {
		cout << buffer<<endl;
	}
	main();

	WSACleanup();
	

}

