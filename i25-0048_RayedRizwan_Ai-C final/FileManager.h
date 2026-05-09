#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Image.h"
#include "Customer.h"
using namespace std;

class FileManager {
public:
    static Image *loadSTB(string path);
    static void saveSTB(string path, Image *img);

    static void loadCustomers(Customer **&customers, int &count);
    static void saveCustomers(Customer **customers, int count);

    static void loadCatalog();
    static void saveCatalog(int filterID, bool status);

    static void appendSession(string cnic, string filterNames, string outPath);
    static void viewAllSessions();
};
