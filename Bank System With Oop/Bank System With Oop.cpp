#include <iostream>
#include "clsLoginScreen.h"
using namespace std;

int main()
{
	
	while (true)
	{

		if (!clsLoginScreen::clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
			
	}

	system("pause>0");
}

