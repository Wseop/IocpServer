# IocpServer
**IOCP 모델을 활용하여 구현한 서버 라이브러리**
## IOCP 설계 구조
![image](https://github.com/Wseop/IocpServer/assets/18005580/ec0cb6a6-e8f9-40a7-bfcc-2b6ed18687bc)
- 각종 소켓 함수는 `IocpObject`에서 호출되며, `IocpEvent(OVERLAPPED)` 객체에 자신의 정보를 넣어서 전달.
  - `OVERLAPPED` 구조체에 `IocpObject`의 정보를 넣어서 전달하므로, `CompletionKey`는 따로 사용하지 않음.
  - 중간에 `IocpObject`가 소멸되는 것을 방지하기 위해 `IocpObject`를 `shared_ptr`로 들고 있게 한다.
```cpp
bool IocpCore::registerObject(shared_ptr<IocpObject> iocpObject)
{
	return INVALID_HANDLE_VALUE != ::CreateIoCompletionPort(iocpObject->getHandle(), _iocpHandle, 0, 0);
}
```
```cpp
class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EEventType eventType);
	~IocpEvent();

	void init();

	inline EEventType getEventType() const { return _eventType; }

	inline shared_ptr<IocpObject> getOwner() const { return _owner; }
	inline void setOwner(shared_ptr<IocpObject> owner) { _owner = owner; }

private:
	EEventType _eventType;
	shared_ptr<IocpObject> _owner;
};
```
- **worker thread**들에 의해 `dispatchEvent()`가 호출되며, 완료된 `IocpEvent(OVERLAPPED)`를 가져와서 Event를 처리.
```cpp
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
```
