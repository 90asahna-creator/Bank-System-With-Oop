#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

class clsFindClientScreen : protected clsScreen
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

	static void ShowFindClient()
	{
		if (!CheckaccessRights(clsUser::pFind))
			return;

		clsScreen::_DrawScreenHeader("\t  Find Client Screen");

		cout << "Please Enter client Account Number: ";
		string AccountNum = clsInputValidation::ReadString();

		while (!clsBankClient::IsClientExit(AccountNum))
		{
			cout << "Account Number is not found, Enter again: ";
			AccountNum = clsInputValidation::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNum);

		if (!Client1.IsEmpty())
		{
			cout << "\nClient Found :-)\n";
			_printClient(Client1);
		}
		else
			cout << "\nClient was not Found :-(\n";
	}
};

