#include "pch.h"
#include "PacketSession.h"
#include "ServerPacketHandler.h"

PacketSession::PacketSession()
{
}

PacketSession::~PacketSession()
{
}

void PacketSession::onConnected()
{
}

void PacketSession::onDisconnected()
{
}

void PacketSession::onRecv(BYTE* packet)
{
	ServerPacketHandler::handlePacket(dynamic_pointer_cast<Session>(shared_from_this()), packet);
}

void PacketSession::onSend(uint32 numOfBytes)
{
}
