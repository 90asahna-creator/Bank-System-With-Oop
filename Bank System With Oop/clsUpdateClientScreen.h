#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

class clsUpdateClientScreen : protected clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient & Client)
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

	static void ShowUpdateClient()
	{
		if (!CheckaccessRights(clsUser::pUpdate))
			return;

		clsScreen::_DrawScreenHeader("\t  Update Client Screen");

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
			cout << "\nAre you sure you want to update this client? y/n: ";
			cin >> Answer;

			if (Answer == 'y' || Answer == 'Y')
			{
				cout << "\n\nUpdate Client Info:";
				cout << "\n_____________________\n";
				_ReadClientInfo(Client1);

				clsBankClient::enSaveResults SaveResult = Client1.Save();

				switch (SaveResult)
				{
				case clsBankClient::enSaveResults::svFaildEmptyObject:
					cout << "\nError account was not saved because it's Empty";
					break;

				case clsBankClient::enSaveResults::svSucceeded:
					cout << "\nAccount Updated Successfully :-)\n";
					_printClient(Client1);
					break;
				}
			}
			
		}

};

