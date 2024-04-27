#include "pch.h"
#include "IocpEvent.h"

IocpEvent::IocpEvent(EEventType eventType) :
	_eventType(eventType),
	_owner(nullptr),
	_session(nullptr)
{
}

IocpEvent::~IocpEvent()
{
}

void IocpEvent::init()
{
	hEvent = 0;
	Offset = 0;
	OffsetHigh = 0;
	Internal = 0;
	InternalHigh = 0;
}
