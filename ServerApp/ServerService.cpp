#include "pch.h"
#include "ServerService.h"
#include "Listener.h"

ServerService::ServerService(NetAddress netAddress, SessionFactory sessionFactory, uint32 acceptCount) :
	Service(netAddress, sessionFactory),
	_listener(make_shared<Listener>(acceptCount))
{
}

ServerService::~ServerService()
{
}

bool ServerService::start()
{
	assert(Service::start());

	_listener->setService(shared_from_this());
	return _listener->startAccept();
}
