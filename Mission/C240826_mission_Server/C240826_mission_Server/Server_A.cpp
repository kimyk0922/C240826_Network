#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string>
#include <time.h>
#include <iostream>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

#pragma pack(push, 1)
struct Data
{

	int First;
	char Operator;
	int Second;

};
#pragma pack(pop)

void ErrorHandling(const char* message);

int main(int argc, char* argv[])
{
	WSADATA     wsaData;
	SOCKET      hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	short   port = 3000;
	int     szClntAddr;
	char    message[] = "������ ��ƿ�~";
	string  problem;
	string  anwser;

	char    buffer[1024] = { 0, };

	srand(time(nullptr));

	// ���� �ʱ�ȭ, ���ϻ���ϱ��� �ʱ�ȭ �ؾ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	// TCP ���ϻ���
	hServSock = socket(AF_INET, SOCK_STREAM, 0);


	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error!");

	

	// ������ �ּ�����
	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);  // ���� PC IP�ּ� ���
	servAddr.sin_port = htons(port);        // ��Ʈ��ȣ

	// �ּ� ����
	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error!");

	// ���� ������ �ְ�
	if (listen(hServSock, 5) == SOCKET_ERROR)    // ���Ӵ�� 5
		ErrorHandling("listen() error!");

	

	while (1)
	{
		// ���� ����
		szClntAddr = sizeof(clntAddr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);   // Ŭ���̾�Ʈ�� ��� ��

		if (hClntSock == INVALID_SOCKET)
			ErrorHandling("accept() error!");


		Data Packet;

		Packet.First = rand() % 100 + 1;
		Packet.Second = rand() % 100 + 1;
		

		char a = Packet.First;
		char b = Packet.Second;
		char d = rand() % 4;

		if (d == 0)
		{

			char c = a + b;
			Packet.Operator = '+';
			
			sprintf(buffer, "%d", c);
			anwser = buffer;

		}
		else if (d == 1)
		{
			
			char c = a - b;
			Packet.Operator = '-';

			sprintf(buffer, "%d", c);
			anwser = buffer;

		}
		else if (d == 2)
		{
			
			char c = a * b;
			Packet.Operator = '*';

			sprintf(buffer, "%d", c);
			anwser = buffer;

		}
		else if (d == 3)
		{

			char c = a / b;
			Packet.Operator = '/';

			sprintf(buffer, "%d", c);
			anwser = buffer;

		}

		printf("% d % c % d", Packet.First, Packet.Operator, Packet. Second);

		Packet.First = htons(Packet.First);
		Packet.Second = htons(Packet.Second);
		
		cout << problem << endl;

		char Buffer[5];
		memcpy(Buffer, &Packet, 5);


		send(hClntSock, Buffer, sizeof(Buffer), 0);

//		send(hClntSock, (char*)(&Packet), sizeof(Packet), 0);

		int recvlen = recv(hClntSock, buffer, sizeof(buffer), 0);

		if (recvlen > 0)
		{
			printf("%s\n", buffer);
			if (strcmp(buffer, anwser.c_str()) == 0)
			{
				send(hClntSock, message, sizeof(message), 0);
				closesocket(hClntSock);
			}
			else
			{
				closesocket(hClntSock);
			}
		}
	}


	closesocket(hServSock);
	WSACleanup();

	return 0;
}

void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}