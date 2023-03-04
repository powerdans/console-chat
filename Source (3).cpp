#include<iostream>
#include<Windows.h>


#include "Messege.h"
#include "Messanger.h"
#include "UserMessanger.h"


using namespace std;

void EnterUserMessanger(UserMessanger userMessanger);
void WorkPrivateChats(UserMessanger& userMessanger);
void WorkGeneralChat(UserMessanger& userMessanger);


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);



	Messanger messanger;
	int choice;
	do
	{

		cout << "\n\n[Мессенджер]\n"
  			 << "1) Вход\n"
			 << "2) Регистрация\n"
			 << "0) Выход\n"
			 << "Выберите пункт: ";
		cin >> choice;

		if (choice == 1 || choice == 2)
		{
			User userData;
			cout << "Введите логин: ";
			cin >> userData.login;
			cout << "Введите пароль: ";
			cin >> userData.password;
			
			try
			{
				if (choice == 1)
				{
					EnterUserMessanger(messanger.SignIn(userData));
				}
				else
				{
					cout << "Введите имя: ";
					cin >> userData.name;
					EnterUserMessanger(messanger.SignUp(userData));
				}
			}
			catch (exception ex)
			{
				cout << "\n\nError! - " << ex.what();
			}
		}

	} while (choice != 0);



	system("pause");
	return 0;
}


void EnterUserMessanger(UserMessanger userMessanger)
{
	int choice;
	do
	{
		const User* userInfo = userMessanger.GetUserInfo();
		cout << "\n\n[Пользователь: " << userInfo->login << " (" << userInfo->name << ") ]\n"
			 << "1) Личные чаты\n"
			 << "2) Общий чат\n"
			 << "0) Выход\n"
			 << "Выберите пункт: ";
		cin >> choice;


		switch (choice)
		{
		case 1:
			WorkPrivateChats(userMessanger);
			break;

		case 2:
			WorkGeneralChat(userMessanger);
			break;

		default:
			break;
		}
		

	} while (choice != 0);
}


void OutputUsersList(std::vector<const User*>& users)
{
	for (int i = 0; i < users.size(); i++)
	{
		cout << i+1 << ") " << users[i]->login << " (" << users[i]->name << ")\n";
	}
}

void OutputMesseges(std::vector<const Messege*>& msgs)
{
	if (msgs.size() == 0)
	{
		cout << "Сообщений нет\n\n";
		return;
	}

	for (int i = 0; i < msgs.size(); i++)
	{
		cout << msgs[i]->GetUser().login << ":\n" << msgs[i]->GetText() << "\n\n";
	}
}



void WorkPrivateChats(UserMessanger& userMessanger)
{
	int choice;
	do
	{

		cout << "\n\n[Личные чаты]\n"
			 << "1) Существующие чаты\n"
			 << "2) Пользователи с кем нет диалога\n"
			 << "0) Выход\n"
			 << "Выберите пункт: ";
		cin >> choice;

		if (choice == 1 || choice == 2)
		{
			std::vector<const User*> users;
			if (choice == 1)
			{
				users = userMessanger.GetUsersExistingChats();
			}
			else
			{
				users = userMessanger.GetUsersNonExistingChats();
			}
			OutputUsersList(users);
			cout << "Выберите пользователя для отправки сообщения или 0 для выхода\n";
			cin >> choice;
			if (choice != 0)
			{
				const User* selectUser = users[choice - 1];
				std::vector<const Messege*> messeges = userMessanger.GetMessegeFromChatWith(*selectUser);
				OutputMesseges(messeges);

				string text;
				cout << "Ваше сооющение: ";
				cin.ignore();
				getline(cin, text);
				userMessanger.SendMessegeChat(*selectUser, text);
			}


			choice = -1;
		}


	} while (choice != 0);
}

void WorkGeneralChat(UserMessanger& userMessanger)
{
	int choice;
	do
	{

		cout << "\n\n[Общий чат]\n"
			 << "1) Просмотр чата\n"
			 << "2) Отправить сообщения\n"
			 << "0) Выход\n"
			 << "Выберите пункт: ";
		cin >> choice;


		switch (choice)
		{
		case 1:
			{
				std::vector<const Messege*> messeges = userMessanger.GetMessegeFromGeneralChat();
				OutputMesseges(messeges);
			}
			break;

		case 2:
			{
				string text;
				cout << "Ваше сооющение: ";
				cin.ignore();
				getline(cin, text);
				userMessanger.SendMessegeGenetalChat(text);
			}
			break;

		default:
			break;
		}


	} while (choice != 0);
}