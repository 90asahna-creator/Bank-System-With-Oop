#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

class clsWithdrawScreen : protected clsScreen
{
private:

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

	static string _ReadAccountNum()
	{
		string n;
		cout << "\nPlease Enter client Account Number: ";
		cin >> n;

		return n;
	}

public:

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t  Withdraw Screen");

		string AccountNum = _ReadAccountNum();

		while (!clsBankClient::IsClientExit(AccountNum))
		{
			cout << "\nClient with [" << AccountNum << "] does not exist.\n";
			AccountNum = _ReadAccountNum();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNum);
		_printClient(Client1);

		double Amount = 0;
		cout << "\nPlease enter withdraw amount: ";
		Amount = clsInputValidation::ReadDblNumber();

		char ch;
		cout << "\nAre you sure you want to perform this transaction(Y/N): ";
		cin >> ch;

		if (tolower(ch) == 'y')
		{
			if (Client1.Withdraw(Amount))
			{
				cout << "\nAmount Deposited Successfully.\n";
				cout << "\nNew Balance is: " << Client1.AccountBalance << "\n";
			}
			else
			{
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmount to withdraw is: " << Amount;
				cout << "\nYour Balance is: " << Client1.AccountBalance;
			}
		}
		else
			cout << "\nOperation was cancelled.\n";
	}

};

