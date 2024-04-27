#pragma once

class NetAddress
{
public:
	NetAddress();
	NetAddress(const SOCKADDR_IN& sockAddr);
	NetAddress(wstring ip, uint16 port);

	inline const SOCKADDR_IN& getSockAddr() const { return _sockAddr; }
	wstring getIp() const;
	uint16 getPort() const;

private:
	IN_ADDR ipToAddress(const wstring& ip);

private:
	SOCKADDR_IN _sockAddr;
};

