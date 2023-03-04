#pragma once


#include <string>
#include <vector>


#include "User.h"
#include "Chat_p2p.h"





class UserMessanger
{
private:

	User* user;
	std::vector<Chat_p2p*> privateChats;

	Chat* generalChat;

	const std::vector<User*>* allUsers;
	std::vector<Chat_p2p>* allChats;



	void GeneratePrivateChats()
	{
		for (int i = 0; i < allChats->size(); i++)
		{
			if ((*allChats)[i].CheckMembership(*user))
			{
				privateChats.push_back(&(*allChats)[i]);
			}
		}
	}

	std::vector<const User*> AllUserElimination(const std::vector<const User*>& users)
	{
		std::vector<const User*> result;

		for (int i = 0; i < allUsers->size(); i++)
		{
			const User* user = (*allUsers)[i];
			if (user != this->user)
			{
				bool isCompanion = false;
				for (int j = 0; j < users.size(); j++)
				{
					if (user == users[j])
					{
						isCompanion = true;
						break;
					}
				}

				if (!isCompanion)
				{
					result.push_back(user);
				}
			}
		}

		return result;
	}


public:

	UserMessanger(User& user,
					Chat& generalChat,
					const std::vector<User*>& allUsers, std::vector<Chat_p2p>& allChats)
	{
		this->allUsers = &allUsers;
		this->generalChat = &generalChat;

		this->user = &user;
		this->allChats = &allChats;

		GeneratePrivateChats();
	}


	const User* GetUserInfo()
	{
		return user;
	}

	std::vector<const User*> GetUsersExistingChats();
	std::vector<const User*> GetUsersNonExistingChats();
	const std::vector<User*>* GetAllUsers();

	Chat_p2p* GetChatWithUser(const User& user);
	Chat_p2p* CreateChatWithUser(const User& user);

	void SendMessegeChat(const User& receiver, std::string text);
	std::vector<const Messege*> GetMessegeFromChatWith(const User& companion);

	void SendMessegeGenetalChat(std::string text);
	std::vector<const Messege*> GetMessegeFromGeneralChat();
	
};
