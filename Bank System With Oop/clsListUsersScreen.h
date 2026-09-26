#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"


class clsListUsersScreen : protected clsScreen
{
	static void _PrintUserRecordLine(clsUser user)
	{
		cout << setw(8) << left << "" << "| " << left << setw(16) << user.UserName;
		cout << "| " << setw(25) << left  << user.FullName();
		cout << "| " << setw(12) << left << user.Phone;
		cout << "| " << setw(17) << left << user.Email;
		cout << "| " << setw(10) << left << user.Password;
		cout << "| " << setw(12) << left << user.Permissions;
	}

public:

	static void ShowUsersList()
	{
		vector <clsUser> vUsers = clsUser::GetUsersList();
		string Title = "\t  Users List Screen";
		string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s)";

		clsScreen::_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "\n\t_________________________________________________________________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << left << setw(16) << "User Name";
		cout << "| " << setw(25) << left << "FullName";
		cout << "| " << setw(12) << left << "Phone";
		cout << "| " << setw(17) << left << "Email";
		cout << "| " << setw(10) << left << "Password";
		cout << "| " << setw(12) << left << "Permissions";
		cout << setw(8) << left << "\n\t__________________________________________________________________________________________________________\n";

		if (vUsers.size() == 0)
			cout << "\t\t\t\tNo Users Available in the system!\n";

		else
		{
			for (clsUser& u : vUsers)
			{
				_PrintUserRecordLine(u);
				cout << endl;
			}

			cout << "\t_________________________________________________________________________________________________________\n";
		}
	}

};

