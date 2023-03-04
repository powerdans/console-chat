#pragma once


#include <string>
#include <vector>



#include "UserMessanger.h"





class Messanger
{
private:
	
	std::vector<User*> users;
	std::vector<Chat_p2p> chats;
	Chat generalChat;


public:

	~Messanger()
	{
		for (int i = 0; i < users.size(); i++)
		{
			delete users[i];
		}
	}

	UserMessanger SignUp(User& userInfo);
	UserMessanger SignIn(User& userInfo);


};
