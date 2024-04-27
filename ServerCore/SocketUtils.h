#pragma once

class SocketUtils
{
public:
	static void startUp();
	static void cleanUp();

	static SOCKET createSocket();
	static void closeSocket(SOCKET& socket);

	static bool bind(SOCKET socket, const NetAddress& netAddress);
	static bool bindAnyAddress(SOCKET socket, uint16 port);
	static bool listen(SOCKET socket, int32 backlog = SOMAXCONN);

	static bool setLinger(SOCKET socket, uint16 onoff, uint16 linger);
	static bool setReuseAddress(SOCKET socket, bool flag);
	static bool setUpdateAcceptSocket(SOCKET acceptSocket, SOCKET listenSocket);

	static LPFN_CONNECTEX WSAConnect;
	static LPFN_DISCONNECTEX WSADisconnect;
	static LPFN_ACCEPTEX WSAAccept;

private:
	static bool bindWindowsFunction(SOCKET socket, GUID guid, LPVOID* fn);
};

