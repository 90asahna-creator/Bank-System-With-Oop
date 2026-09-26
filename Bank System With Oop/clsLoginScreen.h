#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{
private:

	static void _Login()
	{
		string UserName, Password;
		bool LoginFailed = false;
		do
		{
			if (LoginFailed)
			{
				cout << "Invalid Usernsme/Passwors!\n";
			}
			cout << "Enter Username: ";
			getline(cin >> ws, UserName);
			cout << "Enter Password: ";
			getline(cin >> ws, Password);

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		clsMainScreen::ShowMainMenue();
	}

public:

	static void ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		_Login();
	}

};

