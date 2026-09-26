#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

class clsTotalBalancesScreen : protected clsScreen
{
public:

	static void ShowTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		string Title = "\t  Balances List Screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s)";

		clsScreen::_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "\n\t_____________________________________________________________________________________\n";
		cout << setw(8) << left << "" << "| " << left << setw(16) << "Account Number";
		cout << "| " << left << setw(30) << "Client Name";
		cout << "| " << left << setw(10) << "Balance";
		cout << setw(8) << left << "\n\t_____________________________________________________________________________________\n";

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available in the sysytem!\n";

		else
		{
			for (clsBankClient& c : vClients)
			{
				cout << setw(8) << left << "" << "| " << left << setw(16) << c.AccountNumber();
				cout << "| " << left << setw(30) << c.FullName();
				cout << "| " << left << setw(10) << c.AccountBalance;
				cout << endl;
			}
			cout << "\t_______________________________________________________________________________________\n";
		}

		double TotalBalances = clsBankClient::GetTotalBalances();

		cout << "\n\t\t\t\t\t  Total Balances = " << TotalBalances << endl;
		cout << "\t\t\t\t    ( " << clsUtil::TextOfNum(TotalBalances) << ")\n";
	}
};

