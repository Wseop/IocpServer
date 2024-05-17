#pragma once

#include "PacketHandler.h"

class ClientPacketHandler : public PacketHandler
{
public:
	static void init();

public:
	static shared_ptr<SendBuffer> makeC_Login(const string& userId);
	static shared_ptr<SendBuffer> makeC_Chat(const string& msg);

private:
	static void handleS_Login(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize);
	static void handleS_Chat(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize);
};
