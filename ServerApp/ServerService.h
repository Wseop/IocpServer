#pragma once

#include "Service.h"

class Listener;

class ServerService : public Service
{
public:
	ServerService(NetAddress netAddress, SessionFactory sessionFactory, uint32 acceptCount);
	virtual ~ServerService();

	virtual bool start() override;

private:
	shared_ptr<Listener> _listener;
};

