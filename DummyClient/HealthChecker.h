#pragma once

class JobQueue;
class Session;

class HealthChecker
{
public:
	HealthChecker(shared_ptr<Session> session);
	~HealthChecker();

	inline shared_ptr<JobQueue> getJobQueue() const { return _jobQueue; }

	inline uint64 getSendTick() const { return _sendTick; }

	void sendPing();
	void recvPing();

private:
	shared_ptr<JobQueue> _jobQueue;
	shared_ptr<Session> _session;
	uint64 _sendTick;
};

extern shared_ptr<HealthChecker> gHealthChecker;