#pragma once


#include <vector>


#include "Messege.h"
#include "User.h"





class Chat
{
private:

	std::vector<Messege> messeges;


public:

	virtual void Send(User& user, std::string text);
	const std::vector<Messege>* GetMessages();

};
