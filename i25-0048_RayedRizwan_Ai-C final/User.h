#pragma once
#include <string>
using namespace std;

class User {
protected:
    string CNIC, password, fullName;
public:
    User(string c, string p, string f);
    virtual bool login(string c, string p) = 0;
    void logout();
    virtual void registUser() {}
    string getCNIC() const { return CNIC; }
    string getFullName() const { return fullName; }
    string getPassword() const { return password; }
    virtual ~User() {}
};
