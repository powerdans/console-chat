#include "Chat_p2p.h"

void Chat_p2p::Send(User& userSender, std::string text)
{
    if (CheckMembership(userSender))
    {
        Chat::Send(userSender, text);
    }
}

bool Chat_p2p::CheckMembership(const User& user)
{
    return user1 == &user || user2 == &user;
}

const User& Chat_p2p::GetCompanion(User& user)
{
    if (user1 == &user)
    {
        return *user2;
    }
    else if (user2 == &user)
    {
        return *user1;
    }

    throw std::exception("Пользователь не является членом чата");
}
