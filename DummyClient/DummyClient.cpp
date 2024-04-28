#include "pch.h"
#include "ClientPacketHandler.h"
#include "ClientService.h"
#include "PacketSession.h"
#include "Protocol.pb.h"

int main()
{
    ClientPacketHandler::init();
    shared_ptr<ClientService> service = make_shared<ClientService>(NetAddress("127.0.0.1", 7777), []() { return make_shared<PacketSession>(); });
    assert(service->start());

    shared_ptr<Session> session = service->createSession();
    assert(session->connect());

    
    Protocol::Ping pingPayload;
    while (true)
    {
        session->send(ClientPacketHandler::makePing(&pingPayload));

        this_thread::sleep_for(1s);
    }
}
