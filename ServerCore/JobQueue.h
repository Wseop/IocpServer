#pragma once

class Job;

class JobQueue : public enable_shared_from_this<JobQueue>
{
public:
	JobQueue();

	void pushJob(shared_ptr<Job> job, bool bPushOnly = false);
	void executeJobs();

private:
	atomic<uint32> _jobCount;
	Concurrency::concurrent_queue<shared_ptr<Job>> _jobs;
};

