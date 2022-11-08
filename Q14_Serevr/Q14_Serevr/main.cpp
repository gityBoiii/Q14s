#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>

#include <fstream> // ���� �ޱ� 
#include <sstream>
#include <string>

#pragma comment(lib, "WS2_32.lib") //DLL

using namespace std;

struct Data
{
	int Number1;
	int Number2;
};

//bool ReadFile(std::string filePath, unsigned char** _data, int* datalen)
//{
//	std::ifstream is(filePath, std::ifstream::binary);
//	if (is) {
//		// seekg�� �̿��� ���� ũ�� ����
//		is.seekg(0, is.end);
//		int length = (int)is.tellg();
//		is.seekg(0, is.beg);
//
//		// malloc���� �޸� �Ҵ�
//		unsigned char* buffer = (unsigned char*)malloc(length);
//
//		// read data as a block:
//		is.read((char*)buffer, length);
//		is.close();
//		*_data = buffer;
//		*datalen = length;
//	}
//
//	return true;
//}

int main()
{
	WSAData wsaData;
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Result < 0)
	{
		cout << "Winsock init Error.  " << GetLastError() << endl;
		exit(-1);
	}

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0); //���� �����
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "make socket error.  " << GetLastError() << endl;
		exit(-1);
	}

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN)); // ���� �ʱ�ȭ 
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //host to network long
	ServerSockAddr.sin_port = htons(4848); // host to network short

	//		����, �ּ�, �ּұ���
	int Status = bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));
	if (Status == SOCKET_ERROR)
	{
		cout << "bind error.  " << GetLastError() << endl;
		exit(-1);
	}

	//		���� ���� ���·� 
	Status = listen(ServerSocket, 0);
	if (Status == SOCKET_ERROR)
	{
		cout << "listen error.  " << GetLastError() << endl;
		exit(-1);
	}

	SOCKADDR_IN ClientAddrIn;
	memset(&ClientAddrIn, 0, sizeof(SOCKADDR_IN));
	int ClientLength = sizeof(ClientAddrIn);


	//		Ŭ���̾�Ʈ ���� ���
	//blocking socket
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddrIn, &ClientLength);

	if (ClientSocket == INVALID_SOCKET)
	{
		cout << "accept error.  " << GetLastError() << endl;
		exit(-1);
	}


	//fin.open("E:\\game\\Unreal_Projects\\UR_Cpp_Unreal\\chocolate.jpg");  // fin ������ �̿��� input.txt ������ �����Ѵ�.
	/*ofstream output("data.bin", ios::out | ios::binary);

	char c1 = 'U';
	char c2 = 'V';
	char c3 = 'W';
	char str[] = "apbak";

	output.write(&c1, sizeof(char));
	output.write(str, sizeof(str) - 1);
	output.write(&c2, sizeof(c2));
	output << "anim" << ' ';
	output.put('5');
	output.write(&c3, 1);

	int n1 = 500;
	int n2 = 1000;
	double f = 3.14;
	int arr[5] = { 1, 2, 4, 8, 16 };

	output.write((char*)&n1, sizeof(int));
	output.write((char*)arr, sizeof(arr));
	output << n2 << f;

	output.close();*/
	
	//		���� �б� 
	const string filename = "E:\\game\\Unreal_Projects\\UR_Cpp_Unreal\\chocolate.jpg";
	string str;
	
	//	���� lfs�� ��ȯ 
	ifstream ifs(filename);
	//	���� �б� 
	getline(ifs, str);

	cout << str << endl;
	

	

	//		������ ���� 
	//Data Number;
	
	/*int RecvBytes = recv(ClientSocket, (char*)&str, sizeof(Data), 0);
	cout << "Recv Bytes : " << RecvBytes << endl;*/

	string SendData;
	//SendData = htonl(ntohl(str));
	SendData = str;

	int SentBytes = send(ClientSocket, (char*)&SendData, sizeof(SendData), 0);
	cout << "Sent Bytes : " << SentBytes << endl;
	cout << "Answer : " << str << endl;

	closesocket(ClientSocket);
	closesocket(ServerSocket);

	WSACleanup();
	return 0;
}