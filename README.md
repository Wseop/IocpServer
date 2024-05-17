# IocpServer
**IOCP 모델을 활용하여 구현한 간단한 채팅 서버입니다.**
## 실행 예시
- 3개의 클라이언트로 ID를 입력후 접속하여 일정시간 메세지를 전송후 퇴장.
- 서버는 메세지를 broadcast.
- 다시 접속하여 반복. <br>

[Desktop-2024.05.17-16.08.44.09.webm](https://github.com/Wseop/IocpServer/assets/18005580/3a688005-4d26-487b-a2e1-9270bf9d0eda)

## 목차
[1. IOCP 설계 구조](#iocp-설계-구조)

[2. Packet 직렬화](#packet-직렬화)

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
			cout << "[IocpCore] dispatch error : " << errorCode << endl;
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

<hr>

## Packet 직렬화
**Protocol Buffers 라이브러리를 사용하여 구현하였습니다.**
### Packet 설계
![image](https://github.com/Wseop/IocpServer/assets/18005580/fc5d4189-b753-4b55-8347-7f2c08ca6765)
- Header
  - Packet의 타입
  - Packet의 크기 : Header의 크기 + Payload의 크기
- Payload : Protocol Buffers로 정의한 message <br>
### 직렬화
#### 아래 과정을 통해 전송할 Packet을 바이트의 배열(`vector<BYTE>`) 형태로 변환
1. Packet의 크기 계산
2. `SendBuffer`를 생성하여 `Header` 데이터 밀어넣기
3. `Header`의 뒤에 이어서 `Payload` 데이터 밀어넣기
```cpp
template<typename T>
inline static shared_ptr<SendBuffer> makeSendBuffer(EPacketType packetType, T* payload)
{
	// 1.
	uint32 payloadSize = static_cast<uint32>(payload->ByteSizeLong());
	uint32 packetSize = sizeof(PacketHeader) + payloadSize;
	// 2.
	shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packetSize);
	PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->getBuffer());
	header->packetType = packetType;
	header->packetSize = packetSize;
	// 3.
	assert(payload->SerializeToArray(header + 1, payloadSize));
	return sendBuffer;
}
```
### 역직렬화
#### 아래 과정을 통해 수신한 데이터를 객체로 변환
1. Header Parsing : PacketType과 PacketSize, 그리고 Payload의 주소를 Parsing
2. PacketType에 해당하는 handler함수를 호출
3. 호출된 함수에서 `ParseFromArray()`를 사용하여 `Payload`를 객체로 변환하여 처리
```cpp
void PacketHandler::handlePacket(shared_ptr<Session> session, BYTE* packet)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(packet);
	uint16 packetTypeIndex = static_cast<uint16>(header->packetType);
	BYTE* payload = packet + sHeaderSize;
	uint32 payloadSize = header->packetSize - sHeaderSize;

	packetHandler[packetTypeIndex](session, payload, payloadSize);
}
```
- Login Packet 역직렬화 예시
```cpp
void ServerPacketHandler::handleC_Login(shared_ptr<Session> session, BYTE* payload, uint32 payloadSize)
{
	Protocol::C_Login loginPayload;
	if (loginPayload.ParseFromArray(payload, payloadSize))
	{
		gRoom->enterUser(session, loginPayload.userid());
	}
}
```

<hr>
