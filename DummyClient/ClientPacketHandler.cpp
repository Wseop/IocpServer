#include "pch.h"
#include "ClientPacketHandler.h"
#include "HealthChecker.h"

void ClientPacketHandler::init()
{
	PacketHandler::init();
	
	packetHandler[static_cast<uint16>(EPacketType::Ping)] = handlePing;
}

void ClientPacketHandler::handlePing(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize)
{
	gHealthChecker->recvPing();
}
