#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;


	static clsBankClient _ConvertLineToObject(string line, string Separator = "#//#")
	{
		vector <string> vString = clsString::Split(line, Separator);

		return clsBankClient(UpdateMode, vString[0], vString[1], vString[2], vString[3],
			vString[4], vString[5], stod(vString[6]));
	}

	static string _ConvertObjectToLine(clsBankClient client, string Separator = "#//#")
	{
		string DataLine = "";
		DataLine += client.FirstName + Separator;
		DataLine += client.LastName + Separator;
		DataLine += client.Email + Separator;
		DataLine += client.Phone + Separator;
		DataLine += client.AccountNumber() + Separator;
		DataLine += client.PinCode + Separator;
		DataLine += to_string(client.AccountBalance);

		return DataLine;
	}


	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
				vClients.push_back(_ConvertLineToObject(line));

			MyFile.close();
		}

		return vClients;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsBankClient& c : vClients)
			{
				if (c._MarkForDelete == false)
				  MyFile << _ConvertObjectToLine(c) << endl;
			}

			MyFile.close();
		}
	}

	static void _AddDataLineToFile(string line)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
				MyFile << line << endl;

			MyFile.close();
		}
	}


	void _Update()
	{
		vector <clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient& c : _vClients)
		{
			if (c.AccountNumber() == AccountNumber())
			{
				c = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertObjectToLine(*this));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(EmptyMode, "", "", "", "", "", "", 0);
	}

	//struct stTransferLog;
    string _ConvertTransferLogToLine(double amount, clsBankClient DestinationClient, string UserName, string Separator = "#//#")
	{
		string line = "";
		line += clsDate::DateToString(clsDate()) + " - ";
		line += clsDate::GetTime() + Separator;
		line += _AccountNumber + Separator;
		line += DestinationClient.AccountNumber() + Separator;
		line += to_string(amount) + Separator;
		line += to_string(_AccountBalance) + Separator;
		line += to_string(DestinationClient.AccountBalance) + Separator;
		line += UserName;

		return line;
	}
	
	void _RegisterTransferLogin(double amount, clsBankClient DestinationClient, string UserName)
	{
		fstream MyFile;
		MyFile.open("Transfer Log.txt", ios::out | ios::app);

		string line = _ConvertTransferLogToLine(amount, DestinationClient, UserName);

		if (MyFile.is_open())
		{
			MyFile << line << endl;

			MyFile.close();
		}
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNum, string PinCode, float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNum;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	/*struct stTransferLog
	{
		string DateAndTime;
		string AccountNumOfSourceClient;
		string AccountNumOfDestinationClient;
		float TransferAmount = 0;
		double BalanceOfSourceClient;
		double BalanceOfDestinationClient;
		string UserName;
	};*/

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	bool IsMarkedForDelete()
	{
		return _MarkForDelete;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;



	static clsBankClient Find(string AccountNum)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsBankClient client = _ConvertLineToObject(line);
				if (client.AccountNumber() == AccountNum)
				{
					MyFile.close();
					return client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNum, string PinCode)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsBankClient client = _ConvertLineToObject(line);
				if (client.AccountNumber() == AccountNum && client.PinCode == PinCode)
				{
					MyFile.close();
					return client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}


	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded , svFailAccountNumExists };
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if(IsEmpty())
				return svFaildEmptyObject;;
		}

		case enMode::UpdateMode:
		{
			_Update();
			return svSucceeded;
		}

		case enMode::AddNewMode:
		{
			if (IsClientExit(_AccountNumber))
				return enSaveResults::svFailAccountNumExists;
			else
			{
				_AddNew();

				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}

		}
	}


	static bool IsClientExit(string AccountNum)
	{
		clsBankClient Client = clsBankClient::Find(AccountNum);
		return (!Client.IsEmpty());
	}

	bool Delete()
	{
		vector <clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient& c : _vClients)
		{
			if (c.AccountNumber() == _AccountNumber)
			{
				c._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
		*this = _GetEmptyClientObject();

		return true;
	}
	
	static clsBankClient GetAddNewClientObject(string AccountNum)
	{
		return clsBankClient(AddNewMode, "", "", "", "", AccountNum, "", 0);
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		double Total = 0;

		for (clsBankClient& c : vClients)
			Total += c.AccountBalance;

		return Total;
	}

	bool Deposit(double Amount)
	{
		if (Amount <= 0)
			return false;
		else
		{
			_AccountBalance += Amount;
			Save();
			return true;
		}
		
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance || Amount <= 0)
			return false;
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	
	bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName)
	{
		if (!Withdraw(Amount))
			return false;

		DestinationClient.Deposit(Amount);
		_RegisterTransferLogin(Amount, DestinationClient, UserName);
		return true;
	}

};

