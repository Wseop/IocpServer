#pragma once

class NetAddress
{
public:
	NetAddress();
	NetAddress(const SOCKADDR_IN& sockAddr);
	NetAddress(const string& ip, uint16 port);

	inline const SOCKADDR_IN& getSockAddr() const { return _sockAddr; }
	string getIp() const;
	uint16 getPort() const;

private:
	SOCKADDR_IN _sockAddr;
};

