#include "pch.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"
#include "PacketSession.h"

void ClientPacketHandler::init()
{
	PacketHandler::init();
	
	packetHandler[static_cast<uint16>(EPacketType::S_Login)] = handleS_Login;
}

shared_ptr<SendBuffer> ClientPacketHandler::makeC_Login(const string& userId)
{
	Protocol::C_Login payload;
	payload.set_userid(userId);
	return makeSendBuffer(EPacketType::C_Login, &payload);
}

void ClientPacketHandler::handleS_Login(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize)
{
	Protocol::S_Login loginPayload;
	if (loginPayload.ParseFromArray(payload, payloadSize))
	{
		if (loginPayload.success())
		{
			cout << "로그인 성공" << endl;
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
