#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsDate.h"
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
using namespace std;

class clsUser : public clsPerson
{

private:

	enum enMode { EmptyMode = 0, UpdateMode, AddNewMode };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDeleted = false;

	string _PrepareLogInRecord(string Separator = "#//#")
	{
		string line = "";
		line += clsDate::DateToString(clsDate()) + " - ";
		line += clsDate::GetTime() + Separator;
		line += UserName + Separator;
		line += clsUtil::Encryption(Password) + Separator;
		line += to_string(Permissions);

		return line;
	}

	static clsUser _ConvertLineToObject(string line, string Separator = "#//#")
	{
		vector <string> vString = clsString::Split(line, Separator);

		return clsUser(UpdateMode, vString[0], vString[1], vString[2], vString[3],
			vString[4], clsUtil::Decryption(vString[5]), stod(vString[6]));
	}

	static string _ConvertObjectToLine(clsUser User, string Separator = "#//#")
	{
		string DataLine = "";
		DataLine += User.FirstName + Separator;
		DataLine += User.LastName + Separator;
		DataLine += User.Email + Separator;
		DataLine += User.Phone + Separator;
		DataLine += User._UserName + Separator;
		DataLine += clsUtil::Encryption(User._Password) + Separator;
		DataLine += to_string(User._Permissions);

		return DataLine;
	}


	static vector <clsUser> _LoadUsersDataFromFile()
	{
		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
				vUsers.push_back(_ConvertLineToObject(line));

			MyFile.close();
		}

		return vUsers;
	}

	static void _SaveUsersDataToFile(vector<clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsUser& c : vUsers)
			{
				if (c._MarkedForDeleted == false)
					MyFile << _ConvertObjectToLine(c) << endl;
			}

			MyFile.close();
		}
	}

	static void _AddDataLineToFile(string line)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << line << endl;

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsUser> _vUsers = _LoadUsersDataFromFile();

		for (clsUser& user : _vUsers)
		{
			if (user.UserName == UserName)
			{
				user = *this;
				break;
			}
		}
		_SaveUsersDataToFile(_vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertObjectToLine(*this));
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(EmptyMode, "", "", "", "", "", "", 0);
	}

	struct stLoginRecord;
	static stLoginRecord _ConvertLineToLoginRecord(string line, string seperator = "#//#")
	{
		stLoginRecord Record;
		vector <string> vRecords = clsString::Split(line, seperator);

		Record.DateAndTime = vRecords[0];
		Record.UserName = vRecords[1];
		Record.Password = clsUtil::Decryption(vRecords[2]);
		Record.Permissions = stoi(vRecords[3]);

		return Record;
	}

public:

	struct stLoginRecord
	{
		string DateAndTime;
		string UserName;
		string Password;
		int Permissions;
	};

	enum enPermissions { FullAccess = -1, pShowClientsList = 1, pAdd = 2, pDelete = 4, 
		pUpdate = 8, pFind = 16, pTransactions = 32, pManageUsers = 64, pShowLoginRegister = 128 };

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string UserName, string Password, int permissions) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = permissions;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	bool IsMarkedForDelete()
	{
		return _MarkedForDeleted;
	}


	string GetUserName()
	{
		return _UserName;
	}
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	string GetPassword()
	{
		return _Password;
	}
	void SetPassword(string Password)
	{
		_Password = Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	int GetPermissions()
	{
		return _Permissions;
	}
	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;


	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsUser User = _ConvertLineToObject(line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsUser User = _ConvertLineToObject(line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}


	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded, svFailUserNameExists };
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
				return svFaildEmptyObject;;
		}

		case enMode::UpdateMode:
		{
			_Update();
			return svSucceeded;
		}

		case enMode::AddNewMode:
		{
			if (IsUserExist(_UserName))
				return enSaveResults::svFailUserNameExists;
			else
			{
				_AddNew();

				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}

		}
	}


	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	bool Delete()
	{
		vector <clsUser> _vUsers = _LoadUsersDataFromFile();

		for (clsUser& user : _vUsers)
		{
			if (user.UserName == _UserName)
			{
				user._MarkedForDeleted = true;
				break;
			}
		}

		_SaveUsersDataToFile(_vUsers);
		*this = _GetEmptyUserObject();

		return true;
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(AddNewMode, "", "", "", "", UserName, "", -1);
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool HasPermission(enPermissions permissions)
	{
		return (this->Permissions == -1 || this->Permissions & permissions);
	}

    void RegisterLogIn()
	{
		fstream MyFile;
		MyFile.open("Register Logins.txt", ios::out | ios::app);

		string line = _PrepareLogInRecord();

		if (MyFile.is_open())
		{
			MyFile << line << endl;

			MyFile.close();
		}
	}

	static vector <stLoginRecord> GetLoginsList()
	{
		vector <stLoginRecord> vLogins;

		fstream MyFile;
		MyFile.open("Register Logins.txt", ios::in);

		if (MyFile.is_open())
		{
			string line;

			while (getline(MyFile, line))
				vLogins.push_back(_ConvertLineToLoginRecord(line));
	
			MyFile.close();
		}

		return vLogins;
	}

};

