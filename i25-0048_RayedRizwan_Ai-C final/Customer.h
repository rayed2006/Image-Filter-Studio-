#pragma once
#include "User.h"

class Customer : public User {
private:
    bool isBlocked;
public:
    Customer(string c, string p, string f, bool b);
    bool login(string c, string p) override;
    void registUser() override;
    void viewHistory();
    void loadAndApply();
    bool getIsBlocked() const { return isBlocked; }
    void setIsBlocked(bool b) { isBlocked = b; }
};
