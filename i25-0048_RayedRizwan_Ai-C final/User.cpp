#include "User.h"
#include <iostream>

User::User(string c, string p, string f) : CNIC(c), password(p), fullName(f) {}

void User::logout()
{
    cout << "User " << fullName << " logged out." << endl;
}
