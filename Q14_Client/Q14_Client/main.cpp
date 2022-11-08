#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "WS2_32.lib")



int main()
{
	//		소켓 시작
	WSAData WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	//		메모리 초기화
	sockaddr_in ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = PF_INET; // 주소 체계
	ServerSockAddr.sin_addr.S_un.S_addr = inet_addr("218.145.204.176"); // sockaddr_in
	ServerSockAddr.sin_port = htons(4949);

	//		연결 대기 
	connect(ServerSocket, (sockaddr*)&ServerSockAddr, sizeof(ServerSockAddr));

	//		파일 받기
	FILE* OutputImageFile = fopen("output.jpg", "wb");
	//Client
	char Buffer[1] = { 0, }; //2^10
	int RecvSize = 0;
	do
	{
		RecvSize = recv(ServerSocket, Buffer, sizeof(Buffer), 0); // 한 줄씩

		cout << RecvSize << endl;

		size_t WriteSize = fwrite(Buffer, sizeof(char), RecvSize, OutputImageFile);
	} while (RecvSize > 0); // 끝까지
	
	closesocket(ServerSocket); // 소켓 닫기 

	fclose(OutputImageFile);


	//끝
	WSACleanup();
}