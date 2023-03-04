#include "UserMessanger.h"

std::vector<const User*> UserMessanger::GetUsersExistingChats()
{
    std::vector<const User*> companions;
	for (int i = 0; i < privateChats.size(); i++)
	{
		companions.push_back(&(privateChats[i]->GetCompanion(*user)));
	}

	return companions;
}

std::vector<const User*> UserMessanger::GetUsersNonExistingChats()
{
	std::vector<const User*> companions = GetUsersExistingChats();
	std::vector<const User*> result = AllUserElimination(companions);
	return result;
}

const std::vector<User*>* UserMessanger::GetAllUsers()
{
	return allUsers;
}

Chat_p2p* UserMessanger::GetChatWithUser(const User& user)
{
	Chat_p2p* chat = nullptr;
	for (int i = 0; i < privateChats.size(); i++)
	{
		if (privateChats[i]->CheckMembership(user))
		{
			chat = privateChats[i];
			break;
		}
	}
	return chat;
}

Chat_p2p* UserMessanger::CreateChatWithUser(const User& user)
{
	Chat_p2p* chat = GetChatWithUser(user);
	if (chat == nullptr)
	{
		for (int i = 0; i < allUsers->size(); i++)
		{
			if (&user == (*allUsers)[i])
			{
				allChats->push_back(Chat_p2p(*(this->user), user));
				chat = &((*allChats)[allChats->size() - 1]);
				privateChats.push_back(chat);
				break;
			}
		}
	}

	return chat;
}

void UserMessanger::SendMessegeChat(const User& receiver, std::string text)
{
	Chat_p2p* chat = CreateChatWithUser(receiver);
	if (chat == nullptr)
	{
		throw std::exception("User does not exist");
	}

	chat->Send(*(this->user), text);
}

std::vector<const Messege*> UserMessanger::GetMessegeFromChatWith(const User& companion)
{
	std::vector<const Messege*> messeges;
	Chat_p2p* chat = GetChatWithUser(companion);
	if (chat != nullptr)
	{
		const std::vector<Messege>* sourceMesseges = chat->GetMessages();
		for (int i = 0; i < sourceMesseges->size(); i++)
		{
			messeges.push_back(&((*sourceMesseges)[i]));
		}
	}

	return messeges;
}



void UserMessanger::SendMessegeGenetalChat(std::string text)
{
	generalChat->Send(*user, text);
}

std::vector<const Messege*> UserMessanger::GetMessegeFromGeneralChat()
{
	std::vector<const Messege*> generalChatMesseges;
	const std::vector<Messege>* sourceMesseges = generalChat->GetMessages();
	for (int i = 0; i < sourceMesseges->size(); i++)
	{
		generalChatMesseges.push_back(&((*sourceMesseges)[i]));
	}
	return generalChatMesseges;
}


