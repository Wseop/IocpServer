#pragma once

enum class EPacketType : uint16
{

};

struct PacketHeader
{
	EPacketType packetType;
	uint16 packetSize;
};

class PacketHandler
{
};

