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
			// distribute�߿� job�� ó���Ϸ� ���� ��Ȳ�� �����ϱ� ���� bPushOnly�� true�� �����Ͽ� push.
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
