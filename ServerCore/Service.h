#pragma once

class IocpCore;
class Session;
class JobQueue;

using SessionFactory = function<shared_ptr<Session>(void)>;

class Service : public enable_shared_from_this<Service>
{
public:
	Service(NetAddress netAddress, SessionFactory sessionFactory);
	virtual ~Service();

	virtual bool start() abstract;

	inline const shared_ptr<IocpCore> getIocpCore() const { return _iocpCore; }

	inline const NetAddress& getNetAddress() const { return _netAddress; }

	shared_ptr<Session> createSession();
	void insertSession(shared_ptr<Session> session);
	void eraseSession(shared_ptr<Session> session);
	const set<shared_ptr<Session>>& getSessions() const;

	inline const shared_ptr<JobQueue> getJobQueue() const { return _jobQueue; }

private:
	shared_ptr<IocpCore> _iocpCore;

	NetAddress _netAddress;

	mutex _mutex;
	SessionFactory _sessionFactory;
	set<shared_ptr<Session>> _sessions;

	shared_ptr<JobQueue> _jobQueue;
};

