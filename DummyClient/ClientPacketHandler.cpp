#include "pch.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"
#include "PacketSession.h"

void ClientPacketHandler::init()
{
	PacketHandler::init();
	
	packetHandler[static_cast<uint16>(EPacketType::S_Login)] = handleS_Login;
	packetHandler[static_cast<uint16>(EPacketType::S_Chat)] = handleS_Chat;
}

shared_ptr<SendBuffer> ClientPacketHandler::makeC_Login(const string& userId)
{
	Protocol::C_Login payload;
	payload.set_userid(userId);
	return makeSendBuffer(EPacketType::C_Login, &payload);
}

shared_ptr<SendBuffer> ClientPacketHandler::makeC_Chat(const string& msg)
{
	Protocol::C_Chat payload;
	payload.set_msg(msg);
	return makeSendBuffer(EPacketType::C_Chat, &payload);
}

void ClientPacketHandler::handleS_Login(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize)
{
	Protocol::S_Login loginPayload;
	if (loginPayload.ParseFromArray(payload, payloadSize))
	{
		if (loginPayload.success())
		{
			cout << "로그인 성공" << endl;
			
			if (shared_ptr<PacketSession> packetSession = dynamic_pointer_cast<PacketSession>(session))
			{
				packetSession->setLogin(true);
			}
		}
		else
		{
			// 로그인 실패. 재시도
			cout << "로그인 실패" << endl;

			if (shared_ptr<PacketSession> packetSession = dynamic_pointer_cast<PacketSession>(session))
			{
				packetSession->login();
			}
		}
	}
}

void ClientPacketHandler::handleS_Chat(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize)
{
	Protocol::S_Chat chatPayload;
	if (chatPayload.ParseFromArray(payload, payloadSize))
	{
		if (shared_ptr<PacketSession> packetSession = dynamic_pointer_cast<PacketSession>(session))
		{
			packetSession->recvMsg(chatPayload.msg());
		}
	}
}
