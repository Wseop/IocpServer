#pragma once

#include "IocpObject.h"

class Listener : public IocpObject 
{
public:
	Listener(uint32 acceptCount);
	virtual ~Listener();

	virtual void processEvent(IocpEvent* iocpEvent, uint32 numOfBytes) override;

	bool startAccept();

private:
	void registerAccept(IocpEvent* acceptEvent);
	void processAccept(IocpEvent* acceptEvent);

private:
	const uint32 _acceptCount;
	vector<IocpEvent*> _acceptEvents;
};

