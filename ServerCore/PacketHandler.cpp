#include "pch.h"
#include "PacketHandler.h"

PacketHandlerFunc gPacketHandler[UINT16_MAX];

void PacketHandler::init()
{
	sHeaderSize = sizeof(PacketHeader);

	for (uint32 i = 0; i < UINT16_MAX; i++)
	{
		gPacketHandler[i] = handleInvalid;
	}
}

void PacketHandler::handlePacket(shared_ptr<Session> session, BYTE* packet)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(packet);
	uint16 packetTypeIndex = static_cast<uint16>(header->packetType);
	BYTE* payload = packet + sHeaderSize;
	uint32 payloadSize = header->packetSize - sHeaderSize;
	gPacketHandler[packetTypeIndex](session, payload, payloadSize);
}

void PacketHandler::handleInvalid(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize)
{
	cout << format("[PacketHandler] invalid packet.") << endl;
}
