#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"

class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTransferLogRecordLine(clsBankClient::stTransferLog TransferLog)
	{
		cout << setw(8) << left << "" << "| " << left << setw(25) << TransferLog.DateAndTime;
		cout << "| " << left << setw(16) << TransferLog.SourceAccountNum;
		cout << "| " << left << setw(16) << TransferLog.DestinationAccountNum;
		cout << "| " << left << setw(10) << TransferLog.TransferAmount;
		cout << "| " << left << setw(10) << TransferLog.SrcBalanceAfter;
		cout << "| " << left << setw(10) << TransferLog.desBalanceAfter;
		cout << "| " << left << setw(10) << TransferLog.UserName;
	}

public:

	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLog> vTransferLog = clsBankClient::GetTransferLog();
		string Title = "\t  Transfer Log List Screen";
		string SubTitle = "\t    (" + to_string(vTransferLog.size()) + ") Record(s).";
		clsScreen::_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "\n\t_____________________________________________________________________________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << left << setw(25) << "Date and Time";
		cout << "| " << left << setw(16) << "s.Acct";
		cout << "| " << left << setw(16) << "d.Acct";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(10) << "User";
		cout << setw(8) << left << "\n\t_____________________________________________________________________________________________________________________\n";

		if (vTransferLog.size() == 0)
			cout << "\t\t\t\tNo Transfer Logs Available in the system!\n";
		else
		{
			for (clsBankClient::stTransferLog& t : vTransferLog)
			{
				_PrintTransferLogRecordLine(t);
				cout << endl;
			}
			cout << "\t_____________________________________________________________________________________________________________________\n";
		}
	}
};

