#include "pch.h"
#include "ClientService.h"
#include "PacketSession.h"

ClientService::ClientService(NetAddress netAddress, SessionFactory sessionFactory) :
    Service(netAddress, sessionFactory)
{
}

ClientService::~ClientService()
{
}

bool ClientService::start()
{
    return true;
}
