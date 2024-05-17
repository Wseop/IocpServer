#pragma once

#include "PacketHandler.h"

class ServerPacketHandler : public PacketHandler
{
public:
	static void init();

public:
	static shared_ptr<SendBuffer> makeS_Login(bool bSuccess);

private:
	static void handleC_Login(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize);
};

