#define _WINSOCK_DEPRECATED_NO_WARNINGS 


#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "WS2_32.lib") //DLL

using namespace std;

int main()
{
	WSAData wsaData;
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Result < 0)
	{
		cout << "Winsock init Error.  " << GetLastError() << endl;
		exit(-1);
	}

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "make socket error.  " << GetLastError() << endl;
		exit(-1);
	}

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN)); // 0으로 초기화
	ServerSockAddr.sin_family = PF_INET; // AF: Address Family, PF : Protocol Family
	ServerSockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ServerSockAddr.sin_port = htons(5001); // host to network short

	int Status = connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));
	if (Status == SOCKET_ERROR)
	{
		cout << "bind error.  " << GetLastError() << endl;
		exit(-1);
	}


	const char Message[] = "give me message";
	int SendBytes = send(ServerSocket, Message, strlen(Message) + 1, 0);
	if (SendBytes <= 0)
	{
		cout << "send error.  " << GetLastError() << endl;
		exit(-1);
	}
	char Buffer[1024] = { 0, };
	int RecvBytes = recv(ServerSocket, Buffer, 1024, 0);
	if (RecvBytes <= 0)
	{
		cout << "recv error.  " << GetLastError() << endl;
		exit(-1);
	}

	cout << Buffer << endl;

	closesocket(ServerSocket);

	WSACleanup();
	return 0;
}