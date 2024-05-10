#pragma once

#include "IocpObject.h"

class RecvBuffer;
class SendBuffer;

class Session : public IocpObject
{
	const uint32 BUFFER_SIZE = 0x1000;

public:
	Session();
	virtual ~Session();

	virtual void processEvent(IocpEvent* iocpEvent, uint32 numOfBytes) override;

	inline uint32 getSessionId() const { return _sessionId; }
	inline void setSessionId(uint32 sessionId) { _sessionId = sessionId; }

	inline bool isConnected() const { return _bConnected; }

	inline const NetAddress& getNetAddress() const { return _netAddress; }
	inline void setNetAddress(const NetAddress& netAddress) { _netAddress = netAddress; }

	BYTE* getBuffer();
	uint32 getBufferSize() const;

	bool processAccept(const NetAddress& netAddress);

	bool connect();
	bool disconnect();
	void send(shared_ptr<SendBuffer> sendBuffer);

protected:
	virtual void onConnected() {};
	virtual void onDisconnected() {};
	virtual void onRecv(BYTE* pakcet) {};
	virtual void onSend(uint32 numOfBytes) {};

private:
	bool registerConnect();
	void processConnect();

	bool registerDisconnect();
	void processDisconnect();

	void registerRecv();
	void processRecv(uint32 numOfBytes);
	uint32 processPacket(uint32 numOfBytes);

	void registerSend();
	void processSend(uint32 numOfBytes);

private:
	uint32 _sessionId;

	atomic<bool> _bConnected;

	NetAddress _netAddress;

	shared_ptr<RecvBuffer> _recvBuffer;

	mutex _mutex;
	atomic<bool> _bSendRegistered;
	queue<shared_ptr<SendBuffer>> _sendQueue;

	IocpEvent* _connectEvent;
	IocpEvent* _disconnectEvent;
	IocpEvent* _recvEvent;
	IocpEvent* _sendEvent;
};

