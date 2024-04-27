#include "pch.h"
#include "NetAddress.h"

NetAddress::NetAddress()
{
}

NetAddress::NetAddress(const SOCKADDR_IN& sockAddr) :
	_sockAddr(sockAddr)
{
}

NetAddress::NetAddress(wstring ip, uint16 port)
{
	::memset(&_sockAddr, 0, sizeof(_sockAddr));
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr = ipToAddress(ip);
	_sockAddr.sin_port = ::htons(port);
}

wstring NetAddress::getIp() const
{
	WCHAR buffer[100];
	::InetNtopW(AF_INET, &_sockAddr.sin_addr, buffer, sizeof(buffer) / sizeof(WCHAR));
	return wstring(buffer);
}

uint16 NetAddress::getPort() const
{
	return ::ntohs(_sockAddr.sin_port);
}

IN_ADDR NetAddress::ipToAddress(const wstring& ip)
{
	IN_ADDR address;
	::InetPtonW(AF_INET, ip.c_str(), &address);
	return address;
}
