#include "pch.h"
#include "PacketSession.h"
#include "ClientPacketHandler.h"

PacketSession::PacketSession()
{
}

PacketSession::~PacketSession()
{
}

void PacketSession::login()
{
	cout << "ID ют╥б :";
	cin >> _userId;

	send(ClientPacketHandler::makeC_Login(_userId));
}

void PacketSession::onConnected()
{
	cout << "[PacketSession] connected to server." << endl;

	login();
}

void PacketSession::onDisconnected()
{
}

void PacketSession::onRecv(BYTE* packet)
{
	ClientPacketHandler::handlePacket(dynamic_pointer_cast<Session>(shared_from_this()), packet);
}

void PacketSession::onSend(uint32 numOfBytes)
{
}