#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "WS2_32.lib")



int main()
{
	//		���� ����
	WSAData WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	//		�޸� �ʱ�ȭ
	sockaddr_in ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = PF_INET; // �ּ� ü��
	ServerSockAddr.sin_addr.S_un.S_addr = inet_addr("218.145.204.176"); // sockaddr_in
	ServerSockAddr.sin_port = htons(4949);

	//		���� ��� 
	connect(ServerSocket, (sockaddr*)&ServerSockAddr, sizeof(ServerSockAddr));

	//		���� �ޱ�
	FILE* OutputImageFile = fopen("output.jpg", "wb");
	//Client
	char Buffer[1] = { 0, }; //2^10
	int RecvSize = 0;
	do
	{
		RecvSize = recv(ServerSocket, Buffer, sizeof(Buffer), 0); // �� �پ�

		cout << RecvSize << endl;

		size_t WriteSize = fwrite(Buffer, sizeof(char), RecvSize, OutputImageFile);
	} while (RecvSize > 0); // ������
	
	closesocket(ServerSocket); // ���� �ݱ� 

	fclose(OutputImageFile);


	//��
	WSACleanup();
}