#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"

class clsFindUserScreen : protected clsScreen
{
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n______________________________";
		cout << "\nFirst Name  : " << User.FirstName;
		cout << "\nLast Name   : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n_______________________________\n";
	}

public:

	static void ShowFindUserScreen()
	{
		clsScreen::_DrawScreenHeader("\t Find User Screen");

		cout << "Please Enter UserName: ";
		string UserName = clsInputValidation::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "UserName is not found, Enter again: ";
			UserName = clsInputValidation::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		if (!User.IsEmpty())
		{
			cout << "\nUser Found :-)\n";
			_PrintUser(User);
		}
		else
			cout << "\nUser was not Found :-(\n";
	}

};

