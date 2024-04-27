#pragma once

#include "SendBuffer.h"

enum class EPacketType : uint16
{

};

struct PacketHeader
{
	EPacketType packetType;
	uint32 packetSize;
};

class Session;

using PacketHandlerFunc = function<void(shared_ptr<Session>, BYTE*, uint32)>;
extern PacketHandlerFunc gPacketHandler[UINT16_MAX];

class PacketHandler
{
public:
	static void init();
	static void handlePacket(shared_ptr<Session> session, BYTE* packet);

	static uint32 sHeaderSize;

protected:
	template<typename T>
	inline static shared_ptr<SendBuffer> makeSendBuffer(EPacketType packetType, T* payload)
	{
		uint32 payloadSize = static_cast<uint32>(payload->ByteSizeLong());
		uint32 packetSize = sizeof(PacketHeader) + payloadSize;
		
		shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->getBuffer());
		header->packetType = packetType;
		header->packetSize = packetSize;

		assert(payload->SerializeToArray(header + 1, payloadSize));
		return sendBuffer;
	}

private:
	static void handleInvalid(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize);
};

