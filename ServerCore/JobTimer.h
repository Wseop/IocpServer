#pragma once

class JobQueue;
class Job;

struct ReservedJob
{
	ReservedJob(shared_ptr<JobQueue> jobOwner, shared_ptr<Job> job, uint64 startTick) :
		jobOwner(jobOwner),
		job(job),
		startTick(startTick)
	{}

	bool operator<(const ReservedJob& other) const
	{
		return startTick > other.startTick;
	}

	shared_ptr<JobQueue> jobOwner = nullptr;
	shared_ptr<Job> job = nullptr;
	uint64 startTick = 0;
};

class JobTimer
{
public:
	JobTimer();

	void reserveJob(shared_ptr<JobQueue> jobOwner, shared_ptr<Job> job, uint64 startAfter);
	void distributeReservedJobs();

private:
	atomic<bool> _bDistributing;
	Concurrency::concurrent_priority_queue<shared_ptr<ReservedJob>> _reserveQueue;
};

