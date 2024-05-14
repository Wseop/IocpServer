#include "pch.h"
#include "ClientPacketHandler.h"
#include "HealthChecker.h"
#include "Protocol.pb.h"

void ClientPacketHandler::init()
{
	PacketHandler::init();
	
	packetHandler[static_cast<uint16>(EPacketType::Ping)] = handlePing;
}

void ClientPacketHandler::handlePing(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize)
{
	Protocol::Ping pingPayload;
	if (pingPayload.ParseFromArray(payload, payloadSize))
	{
		gHealthChecker->recvPing();
	}
}
