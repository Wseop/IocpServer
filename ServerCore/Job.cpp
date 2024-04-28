#include "pch.h"
#include "Job.h"

Job::Job(JobFunc&& jobFunc) :
	_jobFunc(jobFunc)
{
}

void Job::execute()
{
	if (_jobFunc)
	{
		_jobFunc();
	}
}
