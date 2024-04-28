#include "pch.h"
#include "ServerPacketHandler.h"
#include "ServerService.h"
#include "PacketSession.h"

int main()
{
    ServerPacketHandler::init();
    shared_ptr<ServerService> service = make_shared<ServerService>(NetAddress("127.0.0.1", 7777), []() { return make_shared<PacketSession>(); }, 10);
    assert(service->start());

    cout << "[ServerApp] ServerApp Start." << endl;

    while (true);
}
