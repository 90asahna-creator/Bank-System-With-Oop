#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PrintLoginRecordLine(clsUser::stLoginRecord record)
	{
		cout << setw(8) << left << "" << "| " << left << setw(30) << record.DateAndTime;
		cout << "| " << setw(15) << left << record.UserName;
		cout << "| " << setw(13) << left << record.Password;
		cout << "| " << setw(12) << left << record.Permissions;
	}

public:

	static void ShowLoginRegisterScreen()
	{
		vector <clsUser::stLoginRecord> vLogins = clsUser::GetLoginsList();

		string Title = "\t  Login Register List Screen";
		string SubTitle = "\t    (" + to_string(vLogins.size()) + ") Record(s)";

		clsScreen::_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "\n\t_________________________________________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/Time";
		cout << "| " << setw(15) << left << "UserName";
		cout << "| " << setw(13) << left << "Password";
		cout << "| " << setw(12) << left << "Permissions";
		cout << setw(8) << left << "\n\t_________________________________________________________________________________\n";

		if (vLogins.size() == 0)
			cout << "\t\t\t\tNo Logins Register Available in the system!\n";

		else
		{
			for (clsUser::stLoginRecord& l : vLogins)
			{
				_PrintLoginRecordLine(l);
				cout << endl;
			}

			cout << "\t_________________________________________________________________________________\n";
		}
	}
};

