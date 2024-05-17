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

void Room::handleChat(shared_ptr<Session> session, const string& msg)
{
	_jobQueue->pushJob(make_shared<Job>(shared_from_this(), &Room::_handleChat, dynamic_pointer_cast<PacketSession>(session), msg));
}

void Room::broadcast(shared_ptr<SendBuffer> sendBuffer)
{
	for (auto iter = _users.begin(); iter != _users.end(); iter++)
	{
		iter->second->send(sendBuffer);
	}
}

void Room::_enterUser(shared_ptr<PacketSession> session, string userId)
{
	auto userIt = _users.find(userId);
	if (userIt == _users.end())
	{
		// 로그인 성공. 유저 추가
		_users[userId] = session;
		session->setUserId(userId);

		cout << format("[Room] {} Enter.", userId) << endl;

		session->send(ServerPacketHandler::makeS_Login(true));

		// 입장 메세지 broadcast
		broadcast(ServerPacketHandler::makeS_Chat(format("========== [{}] Enter ==========", userId)));
	}
	else
	{
		// 이미 존재하는 ID. 로그인 실패 packet 전송
		session->send(ServerPacketHandler::makeS_Login(false));
	}
}

void Room::_exitUser(string userId)
{
	auto userIt = _users.find(userId);
	if (userIt != _users.end())
	{
		// 유저 삭제
		_users.erase(userId);
		cout << format("[Room] {} Exit.", userId) << endl;

		// 퇴장 메세지 broadcast
		broadcast(ServerPacketHandler::makeS_Chat(format("========== [{}] Exit ==========", userId)));
	}
}

void Room::_handleChat(shared_ptr<PacketSession> session, string msg)
{
	string userMsg = format("[{}] > {}", session->getUserId(), msg);
	broadcast(ServerPacketHandler::makeS_Chat(userMsg));
}
