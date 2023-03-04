#include "Chat.h"

void Chat::Send(User& user, std::string text)
{
	messeges.push_back(Messege(user, text));
}

const std::vector<Messege>* Chat::GetMessages()
{
	return &messeges;
}
