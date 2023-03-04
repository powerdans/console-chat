#pragma once


#include "Chat.h"
#include "User.h"





class Chat_p2p : public Chat
{
private:

	const User* user1;
	const User* user2;


public:

	Chat_p2p(const User& user1, const User& user2)
	{
		this->user1 = &user1;
		this->user2 = &user2;
	}

	void Send(User& userSender, std::string text) override;

	bool CheckMembership(const User& user);
	const User& GetCompanion(User& user);

};
