#pragma once

class IocpObject;

class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	bool registerObject(shared_ptr<IocpObject> iocpObject);
	void dispatchEvent(uint32 timeoutMs = INFINITE);

private:
	HANDLE _iocpHandle;
};

