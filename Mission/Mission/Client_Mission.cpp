#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32")

using namespace std;


int main()
{

	WSAData wsaData;
	int Result = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if (Result != 0)
	{

		cout << "error" << endl;
		exit(-1);


	}

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == SOCKET_ERROR)
	{

		cout << "socket error %d", GetLastError();
		exit(-1);

	}

	struct sockaddr_in ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSockAddr.sin_port = htons(3000);

	Result = connect(ServerSocket, (struct sockaddr*)&ServerSockAddr, sizeof(ServerSockAddr));
	if (Result != 0)
	{

		cout << "connect error %d", GetLastError();
		exit(-1);

	}

	cout << "Check" << endl;

	char Buffer[1024] = { 0, };
	int RecvByte = recv(ServerSocket, Buffer, 1024, 0);
	if (RecvByte <= 0)
	{

		cout << "recv error %d", GetLastError();
		exit(-1);

	}

	cout << Buffer << endl;

	string Temp = Buffer;
	string Num1Str = Temp.substr(0, 2);
	string OpenStr = Temp.substr(2, 1);
	string Num2Str = Temp.substr(3, 2);
	
	int Num1 = atoi(Num1Str.c_str());
	int Num2 = atoi(Num2Str.c_str());
	int Num3 = Num1 + Num2;

	char Message[1024] = { 0, };
	_itoa(Num3, Message, 10);
	string Num3Str = Message;
	


	string MessageStr = Num1Str + OpenStr + Num2Str + '=' + Num3Str;

	int SendLength = send(ServerSocket, MessageStr.c_str(), (int)MessageStr.length(), 0);

	sprintf(Message, "%s from Client", Buffer);
	int SendBytes = send(ServerSocket, Message, (int)strlen(Message), 0);
	if (SendBytes <= 0)
	{

		cout << "send error %d", GetLastError();
		exit(-1);


	}


	closesocket(ServerSocket);

	WSACleanup();

	return 0;

}