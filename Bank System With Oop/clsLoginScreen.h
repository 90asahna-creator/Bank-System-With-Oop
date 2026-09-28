#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsDate.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login()
	{
		short Trials = 3;
		string UserName, Password;
		bool LoginFailed = false;
		do
		{
			if (LoginFailed)
			{
				cout << "\nInvalid Usernsme/Passwors!\n";
				Trials--;
				cout << "You have " << Trials << " Trial(s) to login.\n\n";
			}

			if (Trials == 0)
			{
				cout << "You are Locked after 3 failed trials.\n";
				return false;
			}
				
			cout << "Enter Username: ";
			getline(cin >> ws, UserName);
			cout << "Enter Password: ";
			getline(cin >> ws, Password);

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		CurrentUser.RegisterLogIn();

		clsMainScreen::ShowMainMenue();
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();
	}

};

