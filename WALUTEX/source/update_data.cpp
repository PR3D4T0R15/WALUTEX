#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "update_data.h"
#include <WinSock2.h>
#include <Windows.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

int getDataFromServer()
{
	short PORT = 80;
	const char hostName[] = "api.nbp.pl";

	//init winsock
	WSAData wsadata;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsadata) != 0)
	{
		return 2;
	}

	//socket
	SOCKET sockt = socket(AF_INET, SOCK_STREAM, 0);
	if (sockt < 0)
	{
		return 2;
	}

	//server info
	HOSTENT* host = gethostbyname(hostName);
	if (host == nullptr)
	{
		return 2;
	}

	SOCKADDR_IN sin;
	ZeroMemory(&sin, sizeof(sin));
	sin.sin_port = htons(PORT);
	sin.sin_family = AF_INET;
	memcpy(&sin.sin_addr.S_un.S_addr, host->h_addr_list[0], sizeof(sin.sin_addr.S_un.S_addr));

	//connect
	if (connect(sockt, (const sockaddr *)&sin, sizeof(sin)) != 0)
	{
		return 2;
	}

	const char message[] = "GET /api/exchangerates/tables/C/?format=xml HTTP/1.1\r\n"
    "Host: api.nbp.pl\r\n"
    "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.5) Gecko/20091102 Firefox/3.5.5 (.NET CLR 3.5.30729)\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml,application/json;q=0.9,*/*;q=0.8\r\n"
    "Accept-Language: en-us,en;q=0.5\r\n"
    "Accept-Encoding: gzip,deflate\r\n"
    "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
    "Keep-Alive: 300\r\n"
    "Connection: keep-alive\r\n"
    "Pragma: no-cache\r\n"
		"Cache-Control: no-cache\r\n\r\n";
	if (!send(sockt, message, strlen(message), 0))
	{
		return 2;
	}

	char Buffer[4096];
	char BufferTemp[4096];
	std::string output;

	//while (recv(sockt, BufferTemp, 4096, 0))
	//{
	//	//strcat(Buffer, BufferTemp);
	//	output = BufferTemp;
	//}

	recv(sockt, BufferTemp, 4096, 0);

	closesocket(sockt);
}