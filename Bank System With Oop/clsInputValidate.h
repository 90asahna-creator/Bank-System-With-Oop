#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "clsDate.h"
#include "clsUtil.h"
using namespace std;

class clsInputValidation
{
public:
	static bool IsNumberBetween(short num, short from, short to)
	{
		return (num >= from && num <= to);
	}

	static bool IsNumberBetween(int num, int from, int to)
	{
		if (from > to)
			clsUtil::Swap(from, to);

		return (num >= from && num <= to);
	}

	static bool IsNumberBetween(float num, float from, float to)
	{
		return (num >= from && num <= to);
	}

	static bool IsNumberBetween(double num, double from, double to)
	{
		if (from > to)
			clsUtil::Swap(from, to);

		return (num >= from && num <= to);
	}

	static bool IsDateBetween(clsDate date, clsDate from, clsDate to)
	{
		if (clsDate::IsDate1AfterDate2(from, to))
			clsUtil::Swap(from, to);

		return (clsDate::IsDate1AfterDate2(date, from) || clsDate::IsDate1EqualDate2(date, from)) &&
			(clsDate::IsDate1BeforeDate2(date, to) || clsDate::IsDate1EqualDate2(date, to));
	}


	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		int num;
		while (!(cin >> num))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return num;
	}

	static int ReadIntNumberBetween(int from, int to, string ErrorMessage = "Number is not within range, enter again: ")
	{
		int num = ReadIntNumber();

		while (!IsNumberBetween(num, from, to))
		{
			cout << ErrorMessage;
			num = ReadIntNumber();
		}
		return num;
	}

	static short ReadShortNumberBetween(short from, short to, string ErrorMessage = "Number is not within range, enter again: ")
	{
		short num = ReadIntNumber();

		while (!IsNumberBetween(num, from, to))
		{
			cout << ErrorMessage;
			num = ReadIntNumber();
		}
		return num;
	}


	static double ReadDblNumber(string message2 = "Invalid Number, Enter again:\n")
	{
		double num;
		while (!(cin >> num))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << message2;
		}
		return num;
	}

	static double ReadDblNumberBetween(double from, double to, string message = "Number is not within range, enter again: ")
	{
		double num = ReadDblNumber();

		while (!IsNumberBetween(num, from, to))
		{
			cout << message;
			num = ReadIntNumber();
		}

		return num;
	}


	static bool IsValidDate(clsDate date)
	{
		return clsDate::IsValidDate(date);
	}

	static string ReadString()
	{
		string S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}
};


