#pragma once

class Room : public enable_shared_from_this<Room>
{
public:
	Room();
	~Room();

	void enterUser(shared_ptr<class Session> session, const string& userId);
	void exitUser(const string& userId);

private:
	void _enterUser(shared_ptr<class PacketSession> session, string userId);
	void _exitUser(string userId);

private:
	unordered_map<string, shared_ptr<class Session>> _users;
	shared_ptr<class JobQueue> _jobQueue;
};

extern shared_ptr<Room> gRoom;