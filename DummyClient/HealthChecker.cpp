#include "pch.h"
#include "HealthChecker.h"
#include "JobQueue.h"
#include "Session.h"
#include "ClientPacketHandler.h"
#include "JobTimer.h"
#include "Job.h"

shared_ptr<HealthChecker> gHealthChecker = nullptr;

HealthChecker::HealthChecker(shared_ptr<Session> session) :
	_jobQueue(make_shared<JobQueue>()),
	_session(session),
	_sendTick(0)
{
}

HealthChecker::~HealthChecker()
{
}

void HealthChecker::sendPing()
{
	Protocol::Ping pingPayload;
	_sendTick = ::GetTickCount64();
	_session->send(ClientPacketHandler::makePing(&pingPayload));
}

void HealthChecker::recvPing()
{
	const uint64 currentTick = ::GetTickCount64();
	const uint64 elapsedTick = currentTick - _sendTick;
	cout << format("Ping : {}", elapsedTick) << endl;

	gJobTimer->reserveJob(_jobQueue, make_shared<Job>(gHealthChecker, &HealthChecker::sendPing), 1000);
}
