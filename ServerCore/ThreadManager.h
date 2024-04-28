#pragma once

#include <thread>

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	void launch(function<void(void)> fn);
	void join();

	void executeJobQueue();
	void executeJobTimer();

private:
	mutex _mutex;
	vector<thread> _threads;
};

