#include "pch.h"
#include "IocpCore.h"
#include "IocpObject.h"
#include "IocpEvent.h"

IocpCore::IocpCore() :
	_iocpHandle(::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0))
{
}

IocpCore::~IocpCore()
{
	assert(::CloseHandle(_iocpHandle));
}

bool IocpCore::registerObject(shared_ptr<IocpObject> iocpObject)
{
	return ::CreateIoCompletionPort(iocpObject->getHandle(), _iocpHandle, 0, 0);
}

void IocpCore::dispatch(uint32 timeoutMs)
{
	DWORD numOfBytes = 0;
	ULONG_PTR dummyKey = 0;
	IocpEvent* iocpEvent = nullptr;

	if (::GetQueuedCompletionStatus(_iocpHandle, &numOfBytes, &dummyKey, reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), timeoutMs) == false)
	{
		int32 errorCode = ::WSAGetLastError();
		switch (errorCode)
		{
		case WAIT_TIMEOUT:
			return;
		case ERROR_NETNAME_DELETED:
			// disconnected.
			break;
		default:
			cout << "[IocpCore] dispatch error : %d" << errorCode << endl;
			break;
		}
	}

	if (iocpEvent)
	{
		shared_ptr<IocpObject> iocpObject = iocpEvent->getOwner();
		if (iocpObject)
		{
			iocpObject->dispatch(iocpEvent, numOfBytes);
		}
	}
}
