#pragma once


#include <string>



#include "User.h"





class Messege
{
private:

	User* userSender;
	std::string text;

public:

	Messege(User& user, std::string& text)
		:text(text)
	{
		this->userSender = &user;
	}


	const std::string& GetText() const
	{
		return text;
	}

	const User& GetUser() const
	{
		return *userSender;
	}
};
