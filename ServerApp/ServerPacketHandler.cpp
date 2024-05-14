#include "pch.h"
#include "ServerPacketHandler.h"
#include "Session.h"

void ServerPacketHandler::init()
{
	PacketHandler::init();
	
	packetHandler[static_cast<uint16>(EPacketType::Ping)] = handlePing;
}

void ServerPacketHandler::handlePing(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize)
{
	Protocol::Ping pingPayload;
	if (pingPayload.ParseFromArray(payload, payloadSize))
	{
		session->send(makePing(&pingPayload));
	}
}
