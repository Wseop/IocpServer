#pragma once

extern shared_ptr<class ThreadManager> gThreadManager;
extern shared_ptr<Concurrency::concurrent_queue<shared_ptr<class JobQueue>>> gWaitJobQueue;
extern shared_ptr<class JobTimer> gJobTimer;