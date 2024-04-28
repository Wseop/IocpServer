#include "pch.h"
#include "CoreTLS.h"
#include "JobQueue.h"

thread_local shared_ptr<JobQueue> tJobQueue = nullptr;