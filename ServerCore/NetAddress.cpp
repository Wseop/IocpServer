#include "pch.h"
#include "NetAddress.h"

NetAddress::NetAddress()
{
}

NetAddress::NetAddress(const SOCKADDR_IN& sockAddr) :
	_sockAddr(sockAddr)
{
}

NetAddress::NetAddress(const string& ip, uint16 port)
{
	::memset(&_sockAddr, 0, sizeof(_sockAddr));
	_sockAddr.sin_family = AF_INET;
	::InetPtonA(AF_INET, ip.c_str(), &_sockAddr.sin_addr);
	_sockAddr.sin_port = ::htons(port);
}

string NetAddress::getIp() const
{
	char buffer[100];
	::InetNtopA(AF_INET, &_sockAddr.sin_addr, buffer, sizeof(buffer) / sizeof(char));
	return string(buffer);
}

uint16 NetAddress::getPort() const
{
	return ::ntohs(_sockAddr.sin_port);
}