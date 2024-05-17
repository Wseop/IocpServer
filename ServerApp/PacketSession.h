#pragma once

#include "Session.h"

class PacketSession : public Session
{
public:
	PacketSession();
	virtual ~PacketSession();

	inline const string& getUserId() const { return _userId; }
	inline void setUserId(const string& userId) { _userId = userId; }

protected:
	virtual void onConnected() override;
	virtual void onDisconnected() override;
	virtual void onRecv(BYTE* packet) override;
	virtual void onSend(uint32 numOfBytes) override;

private:
	string _userId;
};

