#include "Admin.h"
#include "FileManager.h"
#include <iostream>
#include <fstream>
using namespace std;

Admin::Admin() : User("admin", "admin123", "System Administrator") {}

bool Admin::login(string c, string p)
{
    return (CNIC == c && password == p);
}

void Admin::manageCatalog()
{
    FileManager::loadCatalog();
    cout << "Enter Filter ID to toggle (0 to exit): ";
    int id;
    cin >> id;
    if (id > 0)
    {
        bool currentStatus = true;
        FileManager::saveCatalog(id, !currentStatus);
        cout << "Filter status toggled." << endl;
    }
}

void Admin::manageCustomers()
{
    Customer **customers = nullptr;
    int count = 0;
    FileManager::loadCustomers(customers, count);

    if (count == 0)
    {
        cout << "No customers found." << endl;
        return;
    }

    cout << "Customer List" << endl;
    for (int i = 0; i < count; i++)
        cout << i + 1 << ". " << customers[i]->getCNIC()
             << " | " << customers[i]->getFullName()
             << " | Blocked: " << customers[i]->getIsBlocked() << endl;

    cout << "\n1.Block/Unblock  2.Delete  0.Back\nChoice: ";
    int ch;
    cin >> ch;

    if (ch == 1)
    {
        cout << "Enter CNIC to block/unblock: ";
        string cnic;
        cin >> cnic;
        for (int i = 0; i < count; i++)
        {
            if (customers[i]->getCNIC() == cnic)
            {
                customers[i]->setIsBlocked(!customers[i]->getIsBlocked());
                cout << "Status updated." << endl;
            }
        }
        FileManager::saveCustomers(customers, count);
    }
    else if (ch == 2)
    {
        cout << "Enter CNIC to delete: ";
        string cnic;
        cin >> cnic;
        Customer **newList = new Customer *[count];
        int newCount = 0;
        for (int i = 0; i < count; i++)
        {
            if (customers[i]->getCNIC() != cnic)
                newList[newCount++] = customers[i];
            else
                delete customers[i];
        }
        delete[] customers;
        customers = newList;
        count = newCount;
        FileManager::saveCustomers(customers, count);
        cout << "Customer deleted." << endl;
    }

    for (int i = 0; i < count; i++)
        delete customers[i];
    delete[] customers;
}

void Admin::viewAllSessions()
{
    ifstream f("sessions.txt");
    string line;
    cout << "All Sessions" << endl;
    if (f.is_open())
    {
        while (getline(f, line))
            cout << line << endl;
        f.close();
    }
    else
        cout << "No sessions found." << endl;
}
