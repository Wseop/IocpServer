#pragma once

#include "IocpObject.h"

class Listener : public IocpObject 
{
public:
	Listener(uint32 acceptCount);
	virtual ~Listener();

	virtual void dispatch(IocpEvent* iocpEvent, uint32 numOfBytes) override;

	bool startAccept();

	void registerAccept(IocpEvent* acceptEvent);
	void processAccept(IocpEvent* acceptEvent);

private:
	const uint32 _acceptCount;
	vector<IocpEvent*> _acceptEvents;
};

