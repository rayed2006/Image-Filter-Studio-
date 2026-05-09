#pragma once
#include "User.h"

class Admin : public User {
public:
    Admin();
    bool login(string c, string p) override;
    void manageCatalog();
    void manageCustomers();
    void viewAllSessions();
};
