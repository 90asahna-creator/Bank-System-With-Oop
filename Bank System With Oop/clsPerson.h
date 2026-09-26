#pragma once
#include <iostream>
using namespace std;

class clsPerson
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:

	clsPerson(string First, string Last, string email, string phone)
	{
		_FirstName = First;
		_LastName = Last;
		_Email = email;
		_Phone = phone;
	}

	void setFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}
	string GetFirstName()
	{
		return _FirstName;
	}
	__declspec(property(get = GetFirstName, put = setFirstName)) string FirstName;

	void setLastName(string LastName)
	{
		_LastName = LastName;
	}
	string GetLastName()
	{
		return _LastName;
	}
	__declspec(property(get = GetLastName, put = setLastName)) string LastName;

	void setEmail(string email)
	{
		_Email = email;
	}
	string GetEmail()
	{
		return _Email;
	}
	__declspec(property(get = GetEmail, put = setEmail)) string Email;

	void setPhone(string phone)
	{
		_Phone = phone;
	}
	string GetPhone()
	{
		return _Phone;
	}
	__declspec(property(get = GetPhone, put = setPhone)) string Phone;

	string FullName()
	{
		return _FirstName + " " + _LastName;
	}
};
