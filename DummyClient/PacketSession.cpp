#include "pch.h"
#include "PacketSession.h"
#include "ClientPacketHandler.h"

PacketSession::PacketSession() :
	_bLogin(false)
{
}

PacketSession::~PacketSession()
{
}

void PacketSession::login()
{
	if (_bLogin)
	{
		return;
	}

	cout << "ID 입력 :";
	cin >> _userId;

	send(ClientPacketHandler::makeC_Login(_userId));
}

void PacketSession::sendMsg(const string& msg)
{
	send(ClientPacketHandler::makeC_Chat(msg));
}

void PacketSession::recvMsg(const string& msg)
{
	cout << msg << endl;
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