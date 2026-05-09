#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include "Admin.h"
#include "Customer.h"
#include "FileManager.h"
using namespace std;

bool isExactly13Digits(const string &s)
{
    if (s.length() != 13)
        return false;
    for (int i = 0; i < 13; i++)
        if (!isdigit(s[i]))
            return false;
    return true;
}

bool isValidPassword(const string &s)
{
    if (s.length() != 9)
        return false;
    bool hasUpper = false, hasDigit = false;
    for (int i = 0; i < 9; i++)
    {
        if (isupper(s[i]))
            hasUpper = true;
        if (isdigit(s[i]))
            hasDigit = true;
    }
    return hasUpper && hasDigit;
}

bool cnicExists(const string &cnic)
{
    ifstream f("customers.txt");
    string line;
    while (getline(f, line))
    {
        if (line.find(cnic + "|") == 0)
        {
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}

bool cnicBlocked(const string &cnic)
{
    ifstream f("blocked_cnics.txt");
    string line;
    while (getline(f, line))
        if (line == cnic)
        {
            f.close();
            return true;
        }
    f.close();
    return false;
}

Customer *findCustomer(const string &cnic, const string &pass)
{
    ifstream f("customers.txt");
    string line;
    while (getline(f, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string c, p, fn, g, ph, ct, b;
        getline(ss, c, '|');
        getline(ss, p, '|');
        getline(ss, fn, '|');
        getline(ss, g, '|');
        getline(ss, ph, '|');
        getline(ss, ct, '|');
        getline(ss, b, '|');
        if (c == cnic && p == pass)
        {
            f.close();
            return new Customer(c, p, fn, (b == "1"));
        }
    }
    f.close();
    return nullptr;
}

void doRegister()
{
    cout << " New Customer Registration" << endl;
    string cnic, pass, confirm, name;

    while (true)
    {
        cout << "Enter CNIC (13 digits): ";
        cin >> cnic;
        if (!isExactly13Digits(cnic))
        {
            cout << "CNIC must be exactly 13 digits." << endl;
            continue;
        }
        if (cnicBlocked(cnic))
        {
            cout << "This CNIC is banned." << endl;
            return;
        }
        if (cnicExists(cnic))
        {
            cout << "CNIC already registered." << endl;
            return;
        }
        break;
    }

    while (true)
    {
        cout << "Enter Password (9 chars, 1 uppercase, 1 digit): ";
        cin >> pass;
        if (!isValidPassword(pass))
        {
            cout << "Invalid password format." << endl;
            continue;
        }
        cout << "Confirm Password: ";
        cin >> confirm;
        if (pass != confirm)
        {
            cout << "Passwords do not match." << endl;
            continue;
        }
        break;
    }

    cout << "Enter Full Name: ";
    cin.ignore();
    getline(cin, name);

    Customer c(cnic, pass, name, false);
    c.registUser();
    cout << "Registration successful!" << endl;
}

void doAdminLogin()
{
    Admin admin;
    string id, pass;
    cout << "Admin ID: ";
    cin >> id;
    cout << "Password: ";
    cin >> pass;

    if (!admin.login(id, pass))
    {
        cout << "Invalid admin credentials." << endl;
        return;
    }

    cout << "Admin login successful." << endl;
    int ch;
    bool running = true;
    while (running)
    {
        cout << "Admin Panel" << endl;
        cout << "1.Manage Catalog  2.Manage Customers  3.View Sessions  4.Logout" << endl;
        cout << "Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            admin.manageCatalog();
            break;
        case 2:
            admin.manageCustomers();
            break;
        case 3:
            admin.viewAllSessions();
            break;
        case 4:
            admin.logout();
            running = false;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }
}

void doCustomerLogin()
{
    string cnic, pass;
    int attempts = 0;

    while (attempts < 3)
    {
        cout << "CNIC: ";
        cin >> cnic;
        cout << "Password: ";
        cin >> pass;

        Customer *c = findCustomer(cnic, pass);
        if (!c)
        {
            attempts++;
            cout << "Invalid credentials. Attempts left: " << (3 - attempts) << endl;
            continue;
        }

        if (!c->login(cnic, pass))
        {
            delete c;
            cout << "Returning to main menu." << endl;
            return;
        }

        cout << "\nWelcome, " << c->getFullName() << "!" << endl;

        int ch;
        bool running = true;
        while (running)
        {
            cout << "Customer Panel" << endl;
            cout << "1.Load Image & Apply Filters  2.View History  3.Logout" << endl;
            cout << "Choice: ";
            cin >> ch;
            switch (ch)
            {
            case 1:
                c->loadAndApply();
                break;
            case 2:
                c->viewHistory();
                break;
            case 3:
                c->logout();
                running = false;
                break;
            default:
                cout << "Invalid choice." << endl;
            }
        }

        delete c;
        return;
    }

    cout << "Too many failed attempts. Returning to main menu." << endl;
}

int main()
{
    int choice;
    bool running = true;
    while (running)
    {
        cout << "IMAGE FILTER STUDIO" << endl;
        cout << "1.Admin Login  2.Customer Login  3.Register  4.Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            doAdminLogin();
            break;
        case 2:
            doCustomerLogin();
            break;
        case 3:
            doRegister();
            break;
        case 4:
            cout << "Goodbye!" << endl;
            running = false;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }
    return 0;
}
