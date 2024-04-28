#include "pch.h"
#include "Session.h"
#include "RecvBuffer.h"
#include "SendBuffer.h"
#include "IocpEvent.h"
#include "Service.h"
#include "IocpCore.h"
#include "PacketHandler.h"

const uint32 BUFFER_SIZE = 0x1000;

Session::Session() :
	_sessionId(0),
	_bConnected(false),
	_recvBuffer(make_shared<RecvBuffer>(BUFFER_SIZE)),
	_bSendRegistered(false),
	_connectEvent(new IocpEvent(EEventType::Connect)),
	_disconnectEvent(new IocpEvent(EEventType::Disconnect)),
	_recvEvent(new IocpEvent(EEventType::Recv)),
	_sendEvent(new IocpEvent(EEventType::Send))
{
}

Session::~Session()
{
	delete _connectEvent;
	delete _disconnectEvent;
	delete _recvEvent;
	delete _sendEvent;
}

void Session::processEvent(IocpEvent* iocpEvent, uint32 numOfBytes)
{
	switch (iocpEvent->getEventType())
	{
	case EEventType::Connect:
		processConnect();
		break;
	case EEventType::Disconnect:
		processDisconnect();
		break;
	case EEventType::Recv:
		processRecv(numOfBytes);
		break;
	case EEventType::Send:
		processSend(numOfBytes);
		break;
	default:
		cout << format("[Session {}] invalid event type.", _sessionId) << endl;
		break;
	}
}

BYTE* Session::getBuffer()
{
	return _recvBuffer->getWritePos();
}

uint32 Session::getBufferSize() const
{
	return _recvBuffer->getFreeSize();
}

bool Session::processAccept(const NetAddress& netAddress)
{
	shared_ptr<Service> service = getService();
	if (service == nullptr)
	{
		cout << format("[Session {}] service is nullptr.", _sessionId) << endl;
		return false;
	}

	shared_ptr<IocpCore> iocpCore = service->getIocpCore();
	if (iocpCore == nullptr)
	{
		cout << format("[Session {}] iocpCore is nullptr.", _sessionId) << endl;
		return false;
	}
	if (iocpCore->registerObject(shared_from_this()) == false)
	{
		cout << format("[Session {}] registerObject fail.", _sessionId) << endl;
		return false;
	}

	_bConnected.store(true);
	_netAddress = netAddress;
	service->insertSession(dynamic_pointer_cast<Session>(shared_from_this()));
	registerRecv();

	return true;
}

bool Session::connect()
{
	if (_bConnected.exchange(true) == true)
	{
		return false;
	}

	if (registerConnect() == false)
	{
		_bConnected.store(false);
		return false;
	}

	return true;
}

bool Session::disconnect()
{
	if (_bConnected.exchange(false) == false)
	{
		return false;
	}

	if (registerDisconnect() == false)
	{
		_bConnected.store(true);
		return false;
	}

	return true;
}

void Session::send(shared_ptr<SendBuffer> sendBuffer)
{
	if (isConnected() == false || sendBuffer == nullptr)
	{
		return;
	}

	{
		lock_guard<mutex> lock(_mutex);

		_sendQueue.push(sendBuffer);
	}

	if (_bSendRegistered.exchange(true) == false)
		registerSend();
}

bool Session::registerConnect()
{
	shared_ptr<Service> service = getService();
	if (service == nullptr)
	{
		cout << format("[Session {}] service is nullptr.", _sessionId) << endl;
		return false;
	}

	shared_ptr<IocpCore> iocpCore = service->getIocpCore();
	if (iocpCore == nullptr)
	{
		cout << format("[Session {}] iocpCore is nullptr.", _sessionId) << endl;
		return false;
	}

	if (iocpCore->registerObject(shared_from_this()) == false ||
		SocketUtils::setReuseAddress(_socket, true) == false ||
		SocketUtils::bindAnyAddress(_socket, 0) == false)
	{
		cout << format("[Session {}] socket initialize fail.", _sessionId) << endl;
		return false;
	}

	_connectEvent->init();
	_connectEvent->setOwner(shared_from_this());

	SOCKADDR_IN serverAddr = service->getNetAddress().getSockAddr();
	DWORD numOfBytes = 0;
	if (SocketUtils::WSAConnect(_socket, reinterpret_cast<const sockaddr*>(&serverAddr), sizeof(serverAddr), nullptr, 0, &numOfBytes, _connectEvent) == false)
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			_connectEvent->setOwner(nullptr);
			cout << format("[Session {}] Connect error : {}", _sessionId, errorCode) << endl;
			return false;
		}
	}

	return true;
}

void Session::processConnect()
{
	_connectEvent->setOwner(nullptr);

	shared_ptr<Service> service = getService();
	if (service == nullptr)
	{
		cout << format("[Session {}] service is nullptr.", _sessionId) << endl;
		return;
	}

	service->insertSession(dynamic_pointer_cast<Session>(shared_from_this()));
	registerRecv();

	onConnected();
}

bool Session::registerDisconnect()
{
	_disconnectEvent->init();
	_disconnectEvent->setOwner(shared_from_this());

	if (SocketUtils::WSADisconnect(_socket, _disconnectEvent, TF_REUSE_SOCKET, 0) == false)
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			_disconnectEvent->setOwner(nullptr);
			cout << format("[Session {}] Disconnect error : {}", _sessionId, errorCode) << endl;
			return false;
		}
	}

	return true;
}

void Session::processDisconnect()
{
	_disconnectEvent->setOwner(nullptr);

	shared_ptr<Service> service = getService();
	if (service == nullptr)
	{
		cout << format("[Session {}] service is nullptr.", _sessionId) << endl;
		return;
	}

	service->eraseSession(dynamic_pointer_cast<Session>(shared_from_this()));

	onDisconnected();

	cout << format("[Session {}] disconnected.", _sessionId) << endl;
}

void Session::registerRecv()
{
	_recvEvent->init();
	_recvEvent->setOwner(shared_from_this());

	WSABUF wsaBuf;
	wsaBuf.buf = reinterpret_cast<char*>(getBuffer());
	wsaBuf.len = getBufferSize();

	DWORD numOfBytes = 0;
	DWORD flags = 0;
	if (::WSARecv(_socket, &wsaBuf, 1, &numOfBytes, &flags, _recvEvent, nullptr) == SOCKET_ERROR)
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			_recvEvent->setOwner(nullptr);
			cout << format("[Session {}] Recv error : {}", _sessionId, errorCode) << endl;
			// TODO. add to JobQueue. retry.
		}
	}
}

void Session::processRecv(uint32 numOfBytes)
{
	_recvEvent->setOwner(nullptr);

	if (numOfBytes == 0 || _recvBuffer->write(numOfBytes) == false)
	{
		disconnect();
		return;
	}

	uint32 processedPacketSize = processPacket(numOfBytes);
	uint32 dataSize = _recvBuffer->getDataSize();
	if (processedPacketSize > dataSize || _recvBuffer->read(processedPacketSize) == false)
	{
		cout << format("[Session {}] recv overflow.", _sessionId) << endl;
		disconnect();
		return;
	}
	_recvBuffer->clean();
	registerRecv();
}

uint32 Session::processPacket(uint32 numOfBytes)
{
	uint32 processedPacketSize = 0;
	BYTE* buffer = _recvBuffer->getReadPos();

	while (true)
	{
		if (processedPacketSize >= numOfBytes)
		{
			break;
		}

		uint32 remainBytes = numOfBytes - processedPacketSize;
		if (remainBytes < PacketHandler::sHeaderSize)
		{
			break;
		}

		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		if (remainBytes < header->packetSize)
		{
			break;
		}

		onRecv(buffer);

		processedPacketSize += header->packetSize;
		buffer += header->packetSize;
	}

	return processedPacketSize;
}

void Session::registerSend()
{
	_sendEvent->init();
	_sendEvent->setOwner(shared_from_this());

	vector<WSABUF> wsaBufs;
	{
		lock_guard<mutex> lock(_mutex);

		while (_sendQueue.empty() == false)
		{
			shared_ptr<SendBuffer> sendBuffer = _sendQueue.front();
			_sendQueue.pop();

			WSABUF wsaBuf;
			wsaBuf.buf = reinterpret_cast<char*>(sendBuffer->getBuffer());
			wsaBuf.len = sendBuffer->getBufferSize();
			wsaBufs.push_back(wsaBuf);
			_sendEvent->pushSendBuffer(sendBuffer);
		}
	}

	DWORD numOfBytes = 0;
	if (::WSASend(_socket, wsaBufs.data(), static_cast<DWORD>(wsaBufs.size()), &numOfBytes, 0, _sendEvent, nullptr) == SOCKET_ERROR)
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			_sendEvent->setOwner(nullptr);
			_sendEvent->clearSendBuffers();
			_bSendRegistered.store(false);
			cout << format("[Session {}] Send error : {}", _sessionId, errorCode) << endl;
		}
	}
}

void Session::processSend(uint32 numOfBytes)
{
	_sendEvent->setOwner(nullptr);
	_sendEvent->clearSendBuffers();

	bool bRegisterSend = false;
	{
		lock_guard<mutex> lock(_mutex);

		if (_sendQueue.empty() == false)
		{
			bRegisterSend = true;
		}
		else
		{
			_bSendRegistered.store(false);
		}
	}
	if (bRegisterSend)
	{
		registerSend();
	}

	onSend(numOfBytes);
}
