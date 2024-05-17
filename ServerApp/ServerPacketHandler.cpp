#include "pch.h"
#include "ServerPacketHandler.h"
#include "Protocol.pb.h"
#include "Session.h"
#include "Room.h"

void ServerPacketHandler::init()
{
	PacketHandler::init();
	
	packetHandler[static_cast<uint16>(EPacketType::C_Login)] = handleC_Login;
}

shared_ptr<SendBuffer> ServerPacketHandler::makeS_Login(bool bSuccess)
{
	Protocol::S_Login payload;
	payload.set_success(bSuccess);
	return makeSendBuffer(EPacketType::S_Login, &payload);
}

void ServerPacketHandler::handleC_Login(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize)
{
	Protocol::C_Login loginPayload;
	if (loginPayload.ParseFromArray(payload, payloadSize))
	{
		gRoom->enterUser(session, loginPayload.userid());
	}
}
