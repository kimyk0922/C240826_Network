#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <iostream>

#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{

//	post =>
//	host order

	int EndianTest = 0x12345678;

	printf("%x\n", EndianTest);

	int BigEndian = htonl(EndianTest);			// ��ǻ�Ϳ��� ���(Network)�� ���� ��
												//	Host to Network
	printf("%x\n", BigEndian);

	int LittleEndian = ntohl(BigEndian);		//	���(Network)���� ��ǻ�ͷ� ���� ��
												//	Network to Host
	printf("%x\n", LittleEndian);


	return 0;									//	hton => Host to Network.
												//	ntoh => Network to Host.


}