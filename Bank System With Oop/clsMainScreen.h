#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsUtil.h"

#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientsScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUserScreen.h"
#include "clsUser.h"
#include "Global.h"
using namespace std;


class clsMainScreen : protected clsScreen
{
private:

    enum enMainMenueOptions 
    {
        eListClients = 1, eAddNewClient, eDeleteClient,
        eUpdateClient, eFindClient, eShowTransactionsMenue, eManageUsers, eExit
    };

	static short _ReadMainMenueOption()
	{
		cout  << "Choose what do you want to do? [1 to 8]? ";
		short Choice = clsInputValidation::ReadShortNumberBetween(1, 8, "Enter Number between 1 to 8? ");
		return Choice;
	}

    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }


    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClient();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientsScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClient();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClient();
    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsScreen();
    }

    static void _ShowManageUsersMenue()
    {
        clsManageUserScreen::ShowManageUsers();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
    }


    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eExit:
            system("cls");
            _Logout();
            //Login();

            break;
        }

    }

public:

	static void ShowMainMenue()
	{
		system("cls");
		cout << "=================================================\n";
		cout << "\t\t  Main Menue Screen\n";
		cout << "=================================================\n";
		cout << " [1] Show Client List.\n";
		cout << " [2] Add New Client.\n";
		cout << " [3] Delete Client.\n";
		cout << " [4] Update Client Info.\n";
		cout << " [5] Find Client.\n";
		cout << " [6] Transactions.\n";
		cout << " [7] Manage Users.\n";
		cout << " [8] Logout.\n";
		cout << "=================================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
	}
};
