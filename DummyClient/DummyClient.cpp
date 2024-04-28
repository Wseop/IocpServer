#include "pch.h"
#include "ClientPacketHandler.h"
#include "ClientService.h"
#include "PacketSession.h"
#include "Protocol.pb.h"
#include "HealthChecker.h"
#include "JobQueue.h"
#include "Job.h"

int main()
{
    ClientPacketHandler::init();
    shared_ptr<ClientService> service = make_shared<ClientService>(NetAddress("127.0.0.1", 7777), []() { return make_shared<PacketSession>(); });
    assert(service->start());

    shared_ptr<Session> session = service->createSession();
    assert(session->connect());
    
    gHealthChecker = make_shared<HealthChecker>(session);
    gHealthChecker->getJobQueue()->pushJob(make_shared<Job>(gHealthChecker, &HealthChecker::sendPing));
    
    while (true);
}
