#pragma once
#include <iostream>
#include "clsDate.h"
#include "Global.h"
using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        cout << "\t\t\t\t\tUser: " << CurrentUser.UserName << endl;
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << "\n\n";
    }

    static bool CheckaccessRights(clsUser::enPermissions Permissions)
    {
        if (!CurrentUser.HasPermission(Permissions))
        {
            cout << "\t\t\t\t\t________________________________________________________";
            cout << "\n\n\t\t\t\t\t\t    Access Denied! Contact your Admin\n";
            cout << "\t\t\t\t\t________________________________________________________";
            return false;
        }
        
        return true;
    }
};

