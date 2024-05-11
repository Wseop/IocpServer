#include "pch.h"
#include "IocpCore.h"
#include "IocpObject.h"
#include "IocpEvent.h"

IocpCore::IocpCore() :
	_iocpHandle(::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0))
{
	assert(_iocpHandle != INVALID_HANDLE_VALUE);
}

IocpCore::~IocpCore()
{
	::CloseHandle(_iocpHandle);
}

bool IocpCore::registerObject(shared_ptr<IocpObject> iocpObject)
{
	// CompletionKey 사용하지 않음. Overlapped(IocpEvent)로 전달.
	return INVALID_HANDLE_VALUE != ::CreateIoCompletionPort(iocpObject->getHandle(), _iocpHandle, 0, 0);
}

void IocpCore::dispatchEvent(uint32 timeoutMs)
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
			iocpObject->processEvent(iocpEvent, numOfBytes);
		}
	}
}
