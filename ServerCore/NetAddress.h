#pragma once

class NetAddress
{
public:
	NetAddress();
	NetAddress(const SOCKADDR_IN& sockAddr);
	NetAddress(string ip, uint16 port);

	inline const SOCKADDR_IN& getSockAddr() const { return _sockAddr; }
	string getIp() const;
	uint16 getPort() const;

private:
	IN_ADDR ipToAddress(const string& ip);

private:
	SOCKADDR_IN _sockAddr;
};

