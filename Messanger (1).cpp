#include "Messanger.h"

UserMessanger Messanger::SignUp(User& userInfo)
{
    if (userInfo.login.empty() || userInfo.password.empty() || userInfo.name.empty())
    {
        throw std::exception("User can not be registered");
    }

    users.push_back(new User(userInfo));

    return UserMessanger(*users[users.size()-1], generalChat, users, chats);
}

UserMessanger Messanger::SignIn(User& userInfo)
{
    User* user = nullptr;
    for (int  i = 0; i < users.size(); i++)
    {
        if (users[i]->login == userInfo.login && users[i]->password == userInfo.password)
        {
            user = users[i];
            break;
        }
    }

    if (user == nullptr)
    {
        throw std::exception("User with this login and password was not found");
    }

    return UserMessanger(*user, generalChat, users, chats);
}
