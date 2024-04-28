#include "pch.h"
#include "ThreadManager.h"
#include "JobQueue.h"
#include "JobTimer.h"

ThreadManager::ThreadManager()
{
}

ThreadManager::~ThreadManager()
{
	join();
}

void ThreadManager::launch(function<void(void)> fn)
{
	lock_guard<mutex> lock(_mutex);

	_threads.push_back(thread(fn));
}

void ThreadManager::join()
{
	for (thread& t : _threads)
	{
		if (t.joinable())
		{
			t.join();
		}
	}
	_threads.clear();
}

void ThreadManager::executeJobQueue()
{
	if (tJobQueue == nullptr && gWaitJobQueue->try_pop(tJobQueue))
	{
		tJobQueue->executeJobs();
	}
}

void ThreadManager::executeJobTimer()
{
	gJobTimer->distributeReservedJobs();
}
