#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"

class clsClientListScreen : protected clsScreen
{

	static void _PrintClientRecordLine(clsBankClient Client)
	{
		cout << setw(8) << left << "" << "| " << left << setw(16) << Client.AccountNumber();
		cout << "| " << left << setw(10) << Client.PinCode;
		cout << "| " << left << setw(30) << Client.FullName();
		cout << "| " << left << setw(10) << Client.Phone;
		cout << "| " << left << setw(10) << Client.AccountBalance;
	}

public:

	static void ShowClientsList()
	{
		if (!CheckaccessRights(clsUser::pShowClientsList))
			return;

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		string Title = "\t  Client List Screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s)";

		clsScreen::_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "\n\t_____________________________________________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << left << setw(16) << "Account Number";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(30) << "Client Name";
		cout << "| " << left << setw(10) << "Phone";
		cout << "| " << left << setw(10) << "Balance";
		cout << setw(8) << left << "\n\t_____________________________________________________________________________________\n";

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available in the system!\n";

		else
		{
			for (clsBankClient& c : vClients)
			{
				_PrintClientRecordLine(c);
				cout << endl;
			}

			cout << "\t_____________________________________________________________________________________\n";
		}
	}
};

