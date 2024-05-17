#pragma once

#include "Session.h"

class PacketSession : public Session
{
public:
	PacketSession();
	virtual ~PacketSession();

	inline const string& getUserId() const { return _userId; }

	inline bool IsLoggedIn() const { return _bLogin; }
	inline void setLogin(bool bFlag) { _bLogin = bFlag; }

	void login();
	void sendMsg(const string& msg);
	void recvMsg(const string& msg);

protected:
	virtual void onConnected() override;
	virtual void onDisconnected() override;
	virtual void onRecv(BYTE* packet) override;
	virtual void onSend(uint32 numOfBytes) override;

private:
	string _userId;
	bool _bLogin;
};

