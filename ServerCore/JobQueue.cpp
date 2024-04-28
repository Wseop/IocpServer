#include "pch.h"
#include "JobQueue.h"
#include "Job.h"

JobQueue::JobQueue() :
	_jobCount(0)
{
}

void JobQueue::pushJob(shared_ptr<Job> job)
{
	const uint32 prevJobCount = _jobCount.fetch_add(1);
	_jobs.push(job);

	if (prevJobCount == 0)
	{
		if (tJobQueue == nullptr)
		{
			tJobQueue = shared_from_this();
			executeJobs();
		}
		else
		{
			gWaitJobQueue->push(shared_from_this());
		}
	}
	else
	{
		gWaitJobQueue->push(shared_from_this());
	}
}

void JobQueue::executeJobs()
{
	uint32 executeCount = 0;
	shared_ptr<Job> job = nullptr;
	while (_jobs.try_pop(job))
	{
		executeCount++;
		job->execute();
	}

	if (_jobCount.fetch_sub(executeCount) != executeCount)
	{
		gWaitJobQueue->push(shared_from_this());
	}

	tJobQueue = nullptr;
}
