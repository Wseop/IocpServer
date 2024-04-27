#pragma once

class IocpEvent;
class Service;

class IocpObject : public enable_shared_from_this<IocpObject>
{
public:
	IocpObject();
	virtual ~IocpObject();

	inline SOCKET getSocket() const { return _socket; }
	inline HANDLE getHandle() const { return reinterpret_cast<HANDLE>(_socket); }

	inline const shared_ptr<Service> getService() const { return _service.lock(); }
	inline void setService(weak_ptr<Service> service) { _service = service; }

	virtual void dispatch(IocpEvent* iocpEvent, uint32 numOfBytes) abstract;

protected:
	SOCKET _socket;

private:
	weak_ptr<Service> _service;
};

