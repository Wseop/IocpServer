#include "pch.h"
#include "Listener.h"
#include "IocpEvent.h"
#include "Service.h"
#include "IocpCore.h"
#include "Session.h"

Listener::Listener(uint32 acceptCount) :
	_acceptCount(acceptCount)
{
}

Listener::~Listener()
{
	for (IocpEvent* acceptEvent : _acceptEvents)
	{
		delete acceptEvent;
	}
	_acceptEvents.clear();
}

void Listener::dispatch(IocpEvent* iocpEvent, uint32 numOfBytes)
{
	assert(iocpEvent->getEventType() == EEventType::Accept);
	processAccept(iocpEvent);
}

bool Listener::startAccept()
{
	shared_ptr<Service> service = getService();
	if (service == nullptr)
	{
		cout << "[Listener] service is nullptr." << endl;
		return false;
	}

	shared_ptr<IocpCore> iocpCore = service->getIocpCore();
	if (iocpCore == nullptr)
	{
		cout << "[Listener] iocpCore is nullptr." << endl;
		return false;
	}

	if (iocpCore->registerObject(shared_from_this()) == false ||
		SocketUtils::setLinger(_socket, 0, 0) == false ||
		SocketUtils::setReuseAddress(_socket, true) == false ||
		SocketUtils::bind(_socket, service->getNetAddress()) == false ||
		SocketUtils::listen(_socket) == false)
	{
		cout << "[Listener] initialize fail" << endl;
		return false;
	}

	for (uint32 i = 0; i < _acceptCount; i++)
	{
		IocpEvent* acceptEvent = new IocpEvent(EEventType::Accept);
		_acceptEvents.push_back(acceptEvent);
		registerAccept(acceptEvent);
	}

	return true;
}

void Listener::registerAccept(IocpEvent* acceptEvent)
{
	shared_ptr<Service> service = getService();
	if (service == nullptr)
	{
		cout << "[Listener] service is nullptr." << endl;
		return;
	}

	acceptEvent->init();
	acceptEvent->setOwner(shared_from_this());
	shared_ptr<Session> session = service->createSession();
	acceptEvent->setSession(session);

	DWORD numOfBytes = 0;
	if (SocketUtils::WSAAccept(_socket, session->getSocket(), session->getBuffer(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &numOfBytes, acceptEvent) == false)
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			acceptEvent->setOwner(nullptr);
			acceptEvent->setSession(nullptr);
			// TODO. add to JobQueue. retry.
			cout << "[Listener] Accept fail." << endl;
		}
	}
}

void Listener::processAccept(IocpEvent* acceptEvent)
{
	shared_ptr<Session> session = acceptEvent->getSession();
	acceptEvent->setSession(nullptr);
	acceptEvent->setOwner(nullptr);

	if (SocketUtils::setUpdateAcceptSocket(session->getSocket(), _socket) == false)
	{
		cout << "[Listener] update accept socket fail." << endl;
		registerAccept(acceptEvent);
		return;
	}

	SOCKADDR_IN clientAddr;
	int32 addrLen = sizeof(clientAddr);
	::memset(&clientAddr, 0, addrLen);
	if (::getpeername(session->getSocket(), reinterpret_cast<sockaddr*>(&clientAddr), &addrLen) == SOCKET_ERROR)
	{
		cout << "[Listener] get client addr fail." << endl;
		registerAccept(acceptEvent);
		return;
	}

	if (session->processAccept(NetAddress(clientAddr)))
	{
		cout << format("[Listener] session {} connected.", session->getSessionId()) << endl;
	}

	registerAccept(acceptEvent);
}
