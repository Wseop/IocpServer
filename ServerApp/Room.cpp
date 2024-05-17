#include "pch.h"
#include "Room.h"
#include "JobQueue.h"
#include "Job.h"
#include "PacketSession.h"
#include "ServerPacketHandler.h"

shared_ptr<Room> gRoom = make_shared<Room>();

Room::Room() :
	_jobQueue(make_shared<JobQueue>())
{
}

Room::~Room()
{
}

void Room::enterUser(shared_ptr<Session> session, const string& userId)
{
	_jobQueue->pushJob(make_shared<Job>(shared_from_this(), &Room::_enterUser, dynamic_pointer_cast<PacketSession>(session), userId));
}

void Room::exitUser(const string& userId)
{
	_jobQueue->pushJob(make_shared<Job>(shared_from_this(), &Room::_exitUser, userId));
}

void Room::_enterUser(shared_ptr<PacketSession> session, string userId)
{
	auto userIt = _users.find(userId);
	if (userIt == _users.end())
	{
		// �α��� ����. ���� �߰�
		_users[userId] = session;
		session->setUserId(userId);

		cout << format("[Room] {} ����.", userId) << endl;

		session->send(ServerPacketHandler::makeS_Login(true));
	}
	else
	{
		// �̹� �����ϴ� ID. �α��� ���� packet ����
		session->send(ServerPacketHandler::makeS_Login(false));
	}
}

void Room::_exitUser(string userId)
{
	auto userIt = _users.find(userId);
	if (userIt != _users.end())
	{
		// ���� ����
		_users.erase(userId);
		cout << format("[Room] {} ����.", userId) << endl;
	}
}
