#include "pch.h"
#include "Service.h"
#include "IocpCore.h"
#include "Session.h"
#include "ThreadManager.h"

Service::Service(NetAddress netAddress, SessionFactory sessionFactory) :
	_iocpCore(make_shared<IocpCore>()),
	_netAddress(netAddress),
	_sessionFactory(sessionFactory)
{
	for (uint32 i = 0; i < thread::hardware_concurrency(); i++)
	{
		gThreadManager->launch([this]()
			{
				while (true)
				{
					_iocpCore->dispatch(10);
					gThreadManager->executeJobQueue();
					gThreadManager->executeJobTimer();
				}
			});
	}
}

Service::~Service()
{
}

shared_ptr<Session> Service::createSession()
{
	static atomic<uint32> sSessionId = 1;

	shared_ptr<Session> session = _sessionFactory();
	session->setSessionId(sSessionId.fetch_add(1));
	session->setService(shared_from_this());
	return session;
}

void Service::insertSession(shared_ptr<Session> session)
{
	if (session != nullptr)
	{
		lock_guard<mutex> lock(_mutex);

		_sessions.insert(session);
	}
}

void Service::eraseSession(shared_ptr<Session> session)
{
	if (session != nullptr)
	{
		lock_guard<mutex> lock(_mutex);

		_sessions.erase(session);
	}
}

const set<shared_ptr<Session>>& Service::getSessions() const
{
	return _sessions;
}
