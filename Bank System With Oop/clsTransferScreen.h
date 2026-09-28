#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

class clsTransferScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n______________________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n_______________________________\n";
	}

	static string _ReadAccountNum(string message)
	{
		cout << message;
		string AccountNum = clsInputValidation::ReadString();
		while (!clsBankClient::IsClientExit(AccountNum))
		{
			cout << "\nClient with [" << AccountNum << "] does not exist, Enter another one: ";
			AccountNum = clsInputValidation::ReadString();
		}
		return AccountNum;
	}

	static float ReadAmount(clsBankClient SourceClient)
	{
		float Amount = 0;

		cout << "\nEnter Transfer amount: ";
		Amount = clsInputValidation::ReadDblNumber();


		while (Amount > SourceClient.AccountBalance || Amount <= 0)
		{
			if(Amount > SourceClient.AccountBalance)
				cout << "\nAmount Exceeds the available Balance, Enter another amount: ";

			if (Amount <= 0)
				cout << "\nInvalid! Transfer amount must be greater than 0, Enter anouther amount: ";

			Amount = clsInputValidation::ReadDblNumber();
		}

		return Amount;
	}

public:

	static void ShowTransferScreen()
	{
			_DrawScreenHeader("\t  Transfer Screen");

			clsBankClient Sourceclient = clsBankClient::Find(_ReadAccountNum("\nPlease Enter Account Number to Transfer From: "));
			_PrintClient(Sourceclient);

			clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNum("\nPlease Enter Account Number to Transfer To: "));
			while (Sourceclient.AccountNumber() == DestinationClient.AccountNumber())
			{
				cout << "\nYou Can't transfer to the same account!\n";
				DestinationClient = clsBankClient::Find(_ReadAccountNum("\nPlease Enter Account Number to Transfer To: "));
			}
			_PrintClient(DestinationClient);

			float Amount = ReadAmount(Sourceclient);

			char answer;
			cout << "\nAre you sure you want to perform this Operation (Y/N): ";
			cin >> answer;

			if (tolower(answer) == 'y')
			{
				if (Sourceclient.Transfer(Amount, DestinationClient))
					cout << "\nTransfer done Successfully\n";
				else
					cout << "\nTransfer Faild\n";
			}

			else
				cout << "\nThe Operation was cancelled.\n";

			_PrintClient(Sourceclient);
			_PrintClient(DestinationClient);
	}
};

