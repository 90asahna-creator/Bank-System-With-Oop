#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"


class clsAddNewClientScreen : protected clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter First Name: ";
		Client.FirstName = clsInputValidation::ReadString();

		cout << "\nEnter Last Name: ";
		Client.LastName = clsInputValidation::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidation::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidation::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidation::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidation::ReadDblNumber();
	}

	static void _PrintClient(clsBankClient Client)
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

	static void ShowAddNewClient()
	{
		if (!CheckaccessRights(clsUser::pAdd))
			return;

		clsScreen::_DrawScreenHeader("\t  Add New Client");

		cout << "Please Enter Account Number: ";
		string AccountNum = clsInputValidation::ReadString();

		while (clsBankClient::IsClientExit(AccountNum))
		{
			cout << "Account Number is already used, Enter again: ";
			AccountNum = clsInputValidation::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNum);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResults::svFaildEmptyObject:
			cout << "\nError account was not saved because it's Empty";
			break;

		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Added Successfully :-)\n";
			_PrintClient(NewClient);
			break;

		case clsBankClient::enSaveResults::svFailAccountNumExists:
			cout << "\nError account was not saved because account number already is used!\n";
			break;
		}

	}
};

