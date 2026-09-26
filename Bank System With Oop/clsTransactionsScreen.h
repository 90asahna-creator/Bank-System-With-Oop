#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

#include "clsDepositScreen.h";
#include "clsWithdrawScreen.h";
#include "clsTotalBalancesScreen.h"

class clsTransactionsScreen : protected clsScreen
{
	enum enTransactionOption { eDeposit = 1, eWithdraw, eTotalBalances, eMainMenue };

	static void GoBackToTransactionsMenue()
	{
		cout << "\nPress any Key to go back to Transactions Menue....";
		system("pause>0");
		ShowTransactionsScreen();
	}

	static short choice()
	{
			cout << "Choose What do you want to do? [1 to 4]: ";
			return clsInputValidation::ReadShortNumberBetween(1, 4);
	}


	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithDrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalances()
	{
		clsTotalBalancesScreen::ShowTotalBalances();
	}


	static void PerformTransactionOperation(enTransactionOption ch)
	{
		system("cls");
		switch (ch)
		{
		case enTransactionOption::eDeposit:
			_ShowDepositScreen();
			GoBackToTransactionsMenue();
			break;

		case enTransactionOption::eWithdraw:
			_ShowWithDrawScreen();
			GoBackToTransactionsMenue();
			break;

		case enTransactionOption::eTotalBalances:
			_ShowTotalBalances();
			GoBackToTransactionsMenue();
			break;

		case enTransactionOption::eMainMenue:
		{

		}
		}
	}

public:

	static void ShowTransactionsScreen()
	{
		if (!CheckaccessRights(clsUser::pTransactions))
			return;

		system("cls");
		cout << "=================================================\n";
		cout << "\t\t  Transactions Menue Screen\n";
		cout << "=================================================\n";
		cout << " [1] Deposit.\n";
		cout << " [2] Withdraw.\n";
		cout << " [3] Total Balances.\n";
		cout << " [4] Main Menue.\n";
		cout << "=================================================\n";
		PerformTransactionOperation((enTransactionOption)choice());
	}

};

