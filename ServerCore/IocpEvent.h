#pragma once

enum class EEventType : uint8
{
	Connect,
	Disconnect,
	Accept,
	Recv,
	Send,
	Invalid
};

class IocpObject;
class Session;
class SendBuffer;

class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EEventType eventType);
	~IocpEvent();

	void init();

	inline EEventType getEventType() const { return _eventType; }

	inline shared_ptr<IocpObject> getOwner() const { return _owner; }
	inline void setOwner(shared_ptr<IocpObject> owner) { _owner = owner; }

	inline shared_ptr<Session> getSession() const { return _session; }
	inline void setSession(shared_ptr<Session> session) { _session = session; }

	inline void pushSendBuffer(shared_ptr<SendBuffer> sendBuffer) { _sendBuffers.push_back(sendBuffer); }
	inline void clearSendBuffers() { _sendBuffers.clear(); }

private:
	EEventType _eventType;
	shared_ptr<IocpObject> _owner;
	shared_ptr<Session> _session;
	vector<shared_ptr<SendBuffer>> _sendBuffers;
};

