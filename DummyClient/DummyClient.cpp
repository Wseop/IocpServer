#include "pch.h"
#include "ClientPacketHandler.h"
#include "ClientService.h"
#include "PacketSession.h"
#include "Protocol.pb.h"
#include "JobQueue.h"
#include "Job.h"

int main()
{
    ClientPacketHandler::init();
    shared_ptr<ClientService> service = make_shared<ClientService>(NetAddress("127.0.0.1", 7777), []() { return make_shared<PacketSession>(); });
    assert(service->start());

    shared_ptr<Session> session = service->createSession();
    assert(session->connect());

    while (true)
    {
        // 1초마다 메세지 전송
        if (shared_ptr<PacketSession> packetSession = dynamic_pointer_cast<PacketSession>(session))
        {
            if (packetSession->IsLoggedIn())
            {
                packetSession->sendMsg(format("Hello I'm {}", packetSession->getUserId()));
            }
        }
        this_thread::sleep_for(1s);
    }
}
