#pragma once

class Room : public enable_shared_from_this<Room>
{
public:
	Room();
	~Room();

	void enterUser(shared_ptr<class Session> session, const string& userId);
	void exitUser(const string& userId);
	
	void handleChat(shared_ptr<class Session> session, const string& msg);

private:
	void broadcast(shared_ptr<class SendBuffer> sendBuffer);

	void _enterUser(shared_ptr<class PacketSession> session, string userId);
	void _exitUser(string userId);

	void _handleChat(shared_ptr<class PacketSession> session, string msg);

private:
	unordered_map<string, shared_ptr<class Session>> _users;
	shared_ptr<class JobQueue> _jobQueue;
};

extern shared_ptr<Room> gRoom;