#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include <Windows.h> //WSASelect , WSASend


#pragma comment(lib, "ws2_32")
#pragma pack(push, 1)

using namespace std;

struct Data
{

	short First;
	char Operator;
	short Second;

};
#pragma pack(pop)
//	struct Memory Padding

int main()
{

//	cout << sizeof(Data);
//	return 0;

	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in ServerSockAddr;

	ZeroMemory(&ServerSockAddr, 0);

	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSockAddr.sin_port = htons(3000);

	connect(ServerSocket, (struct sockaddr*)&ServerSockAddr, sizeof(ServerSockAddr));

	char Buffer[1024] = { 0, };
	int RecvByte = recv(ServerSocket, Buffer, 1024, 0);

	char FirstNumbers[3] = { 0, };
	char SecondNumbers[3] = { 0, };
	char Operator = 0;

	// [][]		[]		[][]
//	FirstNumbers[0] = Buffer[0];
//	FirstNumbers[1] = Buffer[1];
//	Operator = Buffer[2];
//	SecondNumbers[0] = Buffer[3];
//	SecondNumbers[1] = Buffer[4];

	Data Packet;
	memcpy(&Packet, Buffer, 5);

//	int A = atoi(FirstNumbers);
//	int B = atoi(SecondNumbers);

	int A = ntohs(Packet.First);
	int B = ntohs(Packet.Second);

	Operator = Packet.Operator;


	int C = 0;

	if (Operator == '+')
	{
		C = A + B;
	}
	else if (Operator == '-')
	{
		C = A - B;
	}
	else if (Operator == '*')
	{
		C = A * B;
	}
	else if (Operator == '/')
	{
		C = A / B;
	}
	
	char Message[1024] = { 0, };
	sprintf(Message, "%d", C);
	
	int SendByte = send(ServerSocket, Message, 1024, 0);

	RecvByte = recv(ServerSocket, Buffer, 1024, 0);

	WSACleanup();

	return 0;

}