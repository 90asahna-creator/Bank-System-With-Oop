#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "clsDate.h"
using namespace std;

class clsUtil
{
	static void Print_TableHeader()
	{
		cout << "\n\n\t\t\t\tMultiplication Taple From 1 to 10\n\n";
		for (int i = 1; i <= 10; i++)
		{
			cout << "\t" << i;
		}
		cout << "\n___________________________________________________________________________________\n";
	}

	static string ColumnSeperator(int i)
	{
		if (i < 10) return "   |";
		else        return "  |";
	}

public:

	enum encharType { smallLetter = 1, capital, digit, MixChars, special };

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandomNum(int from, int to)
	{
		int randNum = rand() % (to - from + 1) + from;
		return randNum;
	}

	static char get_randomChar(encharType charType)
	{
		if (charType == MixChars)
			charType = (encharType)RandomNum(1, 3);

		switch (charType)
		{

		case encharType::smallLetter:
		{
			return char(RandomNum(97, 122));
			break;
		}
		case encharType::capital:
		{
			return char(RandomNum(65, 90));
			break;
		}
		case encharType::special:
		{
			return char(RandomNum(33, 47));
			break;
		}
		case encharType::digit:
		{
			return char(RandomNum(48, 57));
			break;
		}
		default:
		{
			return char(RandomNum(65, 90));
			break;
		}
		}
	}


	static string Generate_word(encharType charType, short length)
	{
		string word;
		for (int i = 1; i <= length; i++) word += get_randomChar(charType);

		return word;
	}

	static string Generate_key(encharType charType = encharType::capital)
	{
		string key;
		for (int j = 1; j <= 4; j++)
		{
			key += Generate_word(charType, 4);
			if (j < 4) key += "-";
		}

		return key;
	}

	static void Generate_keys(int num, encharType charType = encharType::capital)
	{
		for (int i = 1; i <= num; i++)
		{
			cout << "Key [" << i << "] : ";
			cout << Generate_key(charType) << endl;
		}
	}


	static void Fill_ArrayWithRandomNums(int arr[], short len, int from, int to)
	{
		for (int i = 0; i < len; i++)
		{
			arr[i] = RandomNum(from, to);
		}
	}

	static void Fill_ArrayWithRandomWords(string arr[], short len, encharType charType, short wordLen)
	{
		for (int i = 0; i < len; i++)
		{
			arr[i] = Generate_word(charType, wordLen);
		}
	}

	static void Fill_ArrayWithRandomKeys(string arr[], short len, encharType charType)
	{
		for (int i = 0; i < len; i++)
		{
			arr[i] = Generate_key(charType);
		}
	}



	static void Swap(int& a, int& b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	static void Swap(double& a, double& b)
	{
		double temp = a;
		a = b;
		b = temp;
	}

	static void Swap(bool& a, bool& b)
	{
		bool temp = a;
		a = b;
		b = temp;
	}

	static void Swap(char& a, char& b)
	{
		char temp = a;
		a = b;
		b = temp;
	}

	static void Swap(string& S1, string& S2)
	{
		string temp = S1;
		S1 = S2;
		S2 = temp;
	}

	static void Swap(clsDate& date1, clsDate& date2)
	{
		clsDate::SwapDates(date1, date2);
	}


	static void Shuffle_array(int arr[], int len)
	{
		for (int i = 0; i < len; i++)
		{
			swap(arr[RandomNum(1, len) - 1], arr[RandomNum(1, len) - 1]);
		}
	}

	static void Shuffle_array(string arr[], int len)
	{
		for (int i = 0; i < len; i++)
		{
			swap(arr[RandomNum(1, len) - 1], arr[RandomNum(1, len) - 1]);
		}
	}


	string Tabs(short tabs)
	{
		string t = "";

		for (int i = 0; i < tabs; i++)
		{
			t += "\t";
			cout << t;
		}
		return t;
	}


	static string Encryption(string text, short key)
	{
		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] == ' ')
			{
				text[i] = ' ';
				continue;
			}
			text[i] = char(text[i] + key);
		}
		return text;
	}

	static string Decryption(string text, short key)
	{
		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] == ' ')
			{
				text[i] = ' ';
				continue;
			}
			text[i] = char(text[i] - key);
		}
		return text;
	}

	static string TextOfNum(int num)
	{
	    if (num == 0)
	        return "";
	
	    if (num >= 1 && num <= 19)
	    {
	        string Nums[] = { "", "One", "Tow", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
	    "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
	
	        return Nums[num] + " ";
	    }
	
	    if (num >= 20 && num <= 99)
	    {
	        string arr[] = { "", "", "Twenty", "Thirty", "Fourty", "Fifty", "Sixty", "Seventy",
	            "Eighty", "Ninety" };
	
	        return arr[num/10] + " " + TextOfNum(num % 10);
	    }
	
	    if (num >= 100 && num <= 199)
	    {
	        return "One Hundred " + TextOfNum(num % 100);
	    }
	
	    if (num >= 200 && num <= 999)
	    {
	        return TextOfNum(num / 100) + "Hundreds " + TextOfNum(num % 100);
	    }
	
	    if (num >= 1000 && num <= 1999)
	    {
	        return "One Thousand " + TextOfNum(num % 1000);
	    }
	
	    if (num >= 2000 && num <= 99999)
	    {
	        return TextOfNum(num / 1000) + "Thousands " + TextOfNum(num % 1000);
	    }
	
	    if (num >= 1000000 && num <= 1999999)
	    {
	        return "One Million " + TextOfNum(num % 1000000);
	    }
	
	    if (num >= 2000000 && num <= 999999999)
	    {
	        return TextOfNum(num / 1000000) + "Millions " + TextOfNum(num % 1000000);
	    }
	
	    if (num >= 1000000000 && num <= 1999999999)
	    {
	        return "One Billion " + TextOfNum(num % 1000000000);
	    }
	
	    else
	    {
	        return TextOfNum(num / 1000000000) + "Billions " + TextOfNum(num % 1000000000);
	    }
	}


	static void AddArray_element(int arr[], int num, int& count)
	{
		arr[count] = num;
		count++;
	}

	static void Copy_array(int arr1[], int arr2[], int len1, int& len2)
	{
		for (int i = 0; i < len1; i++)
			AddArray_element(arr2, arr1[i], len2);
	}

	static void reverse_array(int arr1[], int(&arr2)[], int len)
	{
		for (int i = 0; i < len; i++)
		{
			arr2[i] = arr1[len - i - 1];  // imp
		}
	}

	static void print_array(int n[], int len)
	{
		for (int i = 0; i < len; i++)
		{
			cout << n[i] << " ";
		}
		cout << endl;
	}

	static void Print_MultiplicationTable()
	{
		Print_TableHeader();
		for (int i = 1; i <= 10; i++)
		{
			cout << " " << i << ColumnSeperator(i) << "\t";
			for (int j = 1; j <= 10; j++)
			{
				cout << i * j << "\t";
			}
			cout << endl;
		}
	}

	static bool IsPrime(int num)
	{
		for (int i = 2; i <= num / 2; i++)
		{
			if (num % i == 0) return false;
		}
		return true;
	}

	static void Print_primeNums(int n)
	{
		cout << "\nPrime Numbers from 1 to " << n << " are:" << endl;
		for (int i = 1; i <= n; i++)
		{
			if (IsPrime(i)) cout << i << endl;
		}
	}

};
