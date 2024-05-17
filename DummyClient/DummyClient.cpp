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

    srand(time(nullptr));

    while (true)
    {
        // 접속
        shared_ptr<PacketSession> session = dynamic_pointer_cast<PacketSession>(service->createSession());
        session->connect();
        
        // 로그인 대기
        while (session->IsLoggedIn() == false);

        // 3초 간격으로 메세지 전송. 1 ~ 10회 랜덤
        int32 count = rand() % 10 + 1;
        for (uint32 i = 0; i < count; i++)
        {
            session->sendMsg(format("Hello I'm {}", session->getUserId()));
            this_thread::sleep_for(3s);
        }

        // 접속 종료
        session->disconnect();
    }
}
