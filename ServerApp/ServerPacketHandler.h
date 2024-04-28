#pragma once

#include "PacketHandler.h"

class ServerPacketHandler : public PacketHandler
{
public:
	static void init();

private:
	static void handlePing(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize);
};

