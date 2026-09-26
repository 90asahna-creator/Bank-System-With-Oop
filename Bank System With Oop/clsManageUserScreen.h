#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUsersScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUserScreen :protected clsScreen
{
private:

	enum enManageUsersOption { elistUsers = 1, eAddUsers, eDeleteUsers, eUpdateUsers, eFindUsers, ToMainMenue };

	static void _GoBackToManageUsersMenue()
	{
		cout << "\nPress any Key to go back to Manage Users Menue....";
		system("pause>0");
		ShowManageUsers();
	}

	static short _ReadMangeUsersMenueOptions()
	{
		cout << "Choose What do you want to do? [1 to 6]: ";
		short ch = clsInputValidation::ReadShortNumberBetween(1, 6);

		return ch;
	}


	static void _ShowListUsersScreen()
	{
		clsListUsersScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUser();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUsersScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}


	static void _PerformManagementUsersOperations(enManageUsersOption ch)
	{
		system("cls");
		switch (ch)
		{
		case enManageUsersOption::elistUsers:
			_ShowListUsersScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersOption::eAddUsers:
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersOption::eDeleteUsers:
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersOption::eUpdateUsers:
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersOption::eFindUsers:
			_ShowFindUserScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersOption::ToMainMenue:
		{

		}
			
		}

	}

public:

	static void ShowManageUsers()
	{
		if (!CheckaccessRights(clsUser::pDelete))
			return;

		system("cls");
		cout << "=================================================\n";
		cout << "\t\t  Manage Users Menue Screen\n";
		cout << "=================================================\n";
		cout << " [1] List Users.\n";
		cout << " [2] Add New User.\n";
		cout << " [3] Delete User.\n";
		cout << " [4] Update User.\n";
		cout << " [5] Find User.\n";
		cout << " [6] Main Menue.\n";
		cout << "=================================================\n";

		_PerformManagementUsersOperations((enManageUsersOption)_ReadMangeUsersMenueOptions());
	}
};

