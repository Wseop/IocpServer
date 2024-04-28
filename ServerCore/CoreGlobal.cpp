#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "JobQueue.h"
#include "JobTimer.h"

shared_ptr<ThreadManager> gThreadManager = nullptr;
shared_ptr<Concurrency::concurrent_queue<shared_ptr<JobQueue>>> gWaitJobQueue = nullptr;
shared_ptr<JobTimer> gJobTimer = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		SocketUtils::startUp();

		gThreadManager = make_shared<ThreadManager>();
		gWaitJobQueue = make_shared<Concurrency::concurrent_queue<shared_ptr<JobQueue>>>();
		gJobTimer = make_shared<JobTimer>();
	}

	~CoreGlobal()
	{
		SocketUtils::cleanUp();
	}
} gCoreGlobal;