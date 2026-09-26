#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

class clsDepositScreen : protected clsScreen
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

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t  Deposit Screen");

		string AccountNum = _ReadAccountNum();

		while (!clsBankClient::IsClientExit(AccountNum))
		{
			cout << "\nClient with [" << AccountNum << "] does not exist.\n";
			AccountNum = _ReadAccountNum();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNum);
		_printClient(Client1);

		double Amount = 0;
		cout << "\nPlease enter deposit amount: ";
		Amount = clsInputValidation::ReadDblNumber();

		char ch;
		cout << "\nAre you sure you want to perform this transaction(Y/N): ";
		cin >> ch;

		if (tolower(ch) == 'y')
		{
			Client1.Deposit(Amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance is: " << Client1.AccountBalance << "\n";
		}
		else
			cout << "\nOperation was cancelled.\n";

	}

};

