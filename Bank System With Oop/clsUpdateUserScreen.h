#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"

class clsUpdateUserScreen : protected clsScreen
{
	static clsUser::enPermissions _ReadPermissions()
	{
		short Access = 0;
		char ch;
		cout << "\nDo you want to give Full access(Y/N): ";
		cin >> ch;

		if (tolower(ch) == 'y')
			return clsUser::enPermissions(-1);


		cout << "\n\nDo you want to give access to:- \n";

		cout << "\nShow Clients List? Y/N: ";
		cin >> ch;
		if (tolower(ch) == 'y')
			Access += clsUser::enPermissions::pShow;

		cout << "\nAdd New Clients? Y/N: ";
		cin >> ch;
		if (tolower(ch) == 'y')
			Access += clsUser::enPermissions::pAdd;

		cout << "\nDelete Clients? Y/N: ";
		cin >> ch;
		if (tolower(ch) == 'y')
			Access += clsUser::enPermissions::pDelete;

		cout << "\nUpdate Clients? Y/N: ";
		cin >> ch;
		if (tolower(ch) == 'y')
			Access += clsUser::enPermissions::pUpdate;

		cout << "\nFind Clients? Y/N: ";
		cin >> ch;
		if (tolower(ch) == 'y')
			Access += clsUser::enPermissions::pFind;

		cout << "\nTransactions? Y/N: ";
		cin >> ch;
		if (tolower(ch) == 'y')
			Access += clsUser::enPermissions::pTransactions;

		cout << "\nManage Users? Y/N: ";
		cin >> ch;
		if (tolower(ch) == 'y')
			Access += clsUser::enPermissions::pManageUsers;

		return clsUser::enPermissions(Access);
	}

	static void _ReadUserInfo(clsUser& user)
	{
		cout << "\nEnter First Name: ";
		user.FirstName = clsInputValidation::ReadString();

		cout << "\nEnter Last Name: ";
		user.LastName = clsInputValidation::ReadString();

		cout << "\nEnter Email: ";
		user.Email = clsInputValidation::ReadString();

		cout << "\nEnter Phone: ";
		user.Phone = clsInputValidation::ReadString();

		cout << "\nEnter Password: ";
		user.Password = clsInputValidation::ReadString();

		cout << "\nEnter Permissions: ";
		user.Permissions = _ReadPermissions();
	}

	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n______________________________";
		cout << "\nFirst Name  : " << User.FirstName;
		cout << "\nLast Name   : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n_______________________________\n";
	}

public:

	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\t Update User Screen");

		cout << "Please Enter UserName: ";
		string UserName = clsInputValidation::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "UserName is not found, Enter again: ";
			UserName = clsInputValidation::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer = 'n';
		cout << "\nAre you sure you want to update this User? y/n: ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\n\nUpdate User Info:";
			cout << "\n_____________________\n";
			_ReadUserInfo(User);

			clsUser::enSaveResults SaveResult = User.Save();

			switch (SaveResult)
			{
			case clsUser::enSaveResults::svFaildEmptyObject:
				cout << "\nError User was not saved because it's Empty";
				break;

			case clsUser::enSaveResults::svSucceeded:
				cout << "\nUser Updated Successfully :-)\n";
				_PrintUser(User);
				break;
			}
		}

	}

};

