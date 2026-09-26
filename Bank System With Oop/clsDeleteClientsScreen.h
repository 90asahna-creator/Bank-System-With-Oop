#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"


class clsDeleteClientsScreen : protected clsScreen
{
	static void _printClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n______________________________";
		cout << "\nFirst Name  : " << Client.FirstName;
		cout << "\nLast Name   : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n_______________________________\n";
	}

public:

	static void ShowDeleteClientScreen()
	{
		if (!CheckaccessRights(clsUser::pDelete))
			return;

		clsScreen::_DrawScreenHeader("\t Delete Client Screen");

		cout << "Please Enter client Account Number: ";
		string AccountNum = clsInputValidation::ReadString();

		while (!clsBankClient::IsClientExit(AccountNum))
		{
			cout << "Account Number is not found, Enter again: ";
			AccountNum = clsInputValidation::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNum);
		_printClient(Client1);

		char Answer = 'n';
		cout << "\nAre you sure you want to delete this client? y/n: ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (Client1.Delete())
			{
				cout << "\nAccount Deleted Successfully :-)\n";
				_printClient(Client1);
			}

			else
				cout << "\nError Client was not deleted!\n";
		}

	}
};

