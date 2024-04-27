#include "pch.h"
#include "SocketUtils.h"

LPFN_CONNECTEX SocketUtils::WSAConnect = nullptr;
LPFN_DISCONNECTEX SocketUtils::WSADisconnect = nullptr;
LPFN_ACCEPTEX SocketUtils::WSAAccept = nullptr;

void SocketUtils::startUp()
{
	WSADATA wsaData;
	assert(::WSAStartup(MAKEWORD(2, 2), &wsaData) == 0);

	SOCKET dummySocket = createSocket();
	assert(bindWindowsFunction(dummySocket, WSAID_CONNECTEX, reinterpret_cast<LPVOID*>(&WSAConnect)));
	assert(bindWindowsFunction(dummySocket, WSAID_DISCONNECTEX, reinterpret_cast<LPVOID*>(&WSADisconnect)));
	assert(bindWindowsFunction(dummySocket, WSAID_ACCEPTEX, reinterpret_cast<LPVOID*>(&WSAAccept)));

	closeSocket(dummySocket);
}

void SocketUtils::cleanUp()
{
	::WSACleanup();
}

SOCKET SocketUtils::createSocket()
{
	return ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
}

void SocketUtils::closeSocket(SOCKET& socket)
{
	if (socket != INVALID_SOCKET)
	{
		::closesocket(socket);
		socket = INVALID_SOCKET;
	}
}

bool SocketUtils::bind(SOCKET socket, const NetAddress& netAddress)
{
	return SOCKET_ERROR != ::bind(socket, reinterpret_cast<const sockaddr*>(&netAddress.getSockAddr()), sizeof(SOCKADDR_IN));
}

bool SocketUtils::bindAnyAddress(SOCKET socket, uint16 port)
{
	SOCKADDR_IN sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	sockAddr.sin_port = ::htons(port);
	return SOCKET_ERROR != ::bind(socket, reinterpret_cast<const sockaddr*>(&sockAddr), sizeof(sockAddr));
}

bool SocketUtils::listen(SOCKET socket, int32 backlog)
{
	return SOCKET_ERROR != ::listen(socket, backlog);
}

bool SocketUtils::setLinger(SOCKET socket, uint16 onoff, uint16 linger)
{
	LINGER optval;
	optval.l_onoff = onoff;
	optval.l_linger = linger;
	return SOCKET_ERROR != ::setsockopt(socket, SOL_SOCKET, SO_LINGER, reinterpret_cast<const char*>(&optval), sizeof(optval));
}

bool SocketUtils::setReuseAddress(SOCKET socket, bool flag)
{
	return SOCKET_ERROR != ::setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(flag), sizeof(flag));
}

bool SocketUtils::setUpdateAcceptSocket(SOCKET acceptSocket, SOCKET listenSocket)
{
	return SOCKET_ERROR != ::setsockopt(acceptSocket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, reinterpret_cast<const char*>(listenSocket), sizeof(listenSocket));
}

bool SocketUtils::bindWindowsFunction(SOCKET socket, GUID guid, LPVOID* fn)
{
	DWORD bytes = 0;
	return SOCKET_ERROR != ::WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid, sizeof(guid), fn, sizeof(*fn), &bytes, NULL, NULL);
}
