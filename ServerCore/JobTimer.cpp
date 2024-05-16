#include "pch.h"
#include "JobTimer.h"
#include "JobQueue.h"

JobTimer::JobTimer() :
	_bDistributing(false)
{
}

void JobTimer::reserveJob(shared_ptr<JobQueue> jobOwner, shared_ptr<Job> job, uint64 startAfter)
{
	const uint64 startTick = ::GetTickCount64() + startAfter;
	_reserveQueue.push(make_shared<ReservedJob>(jobOwner, job, startTick));
}

void JobTimer::distributeReservedJobs()
{
	if (_bDistributing.exchange(true) == true)
	{
		return;
	}

	const uint64 currentTick = ::GetTickCount64();
	shared_ptr<ReservedJob> reservedJob = nullptr;
	while (_reserveQueue.try_pop(reservedJob))
	{
		if (reservedJob->jobOwner == nullptr || reservedJob->job == nullptr)
		{
			continue;
		}
		else if (reservedJob->startTick <= currentTick)
		{
			// distribute중에 job을 처리하러 들어가는 상황을 방지하기 위해 bPushOnly를 true로 설정하여 push.
			reservedJob->jobOwner->pushJob(reservedJob->job, true);
		}
		else
		{
			_reserveQueue.push(reservedJob);
			break;
		}
	}

	_bDistributing.store(false);
}
