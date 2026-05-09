#include "FileManager.h"
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image *FileManager::loadSTB(string path)
{
    int w, h, ch;
    unsigned char *data = stbi_load(path.c_str(), &w, &h, &ch, 3);
    if (!data)
    {
        cout << "Error: Could not load image " << path << endl;
        return nullptr;
    }

    Image *img = new Image(w, h);
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            int idx = 3 * (i * w + j);
            img->at(i, j).setR(data[idx]);
            img->at(i, j).setG(data[idx + 1]);
            img->at(i, j).setB(data[idx + 2]);
        }

    stbi_image_free(data);
    return img;
}

void FileManager::saveSTB(string path, Image *img)
{
    img->save(path);
}

void FileManager::loadCustomers(Customer **&customers, int &count)
{
    ifstream file("customers.txt");
    string line;
    count = 0;

    while (getline(file, line))
        if (!line.empty())
            count++;

    file.clear();
    file.seekg(0);

    customers = new Customer *[count];
    int i = 0;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string c, p, f, g, ph, ct, b;
        getline(ss, c, '|');
        getline(ss, p, '|');
        getline(ss, f, '|');
        getline(ss, g, '|');
        getline(ss, ph, '|');
        getline(ss, ct, '|');
        getline(ss, b, '|');
        customers[i++] = new Customer(c, p, f, (b == "1"));
    }
    file.close();
}

void FileManager::saveCustomers(Customer **customers, int count)
{
    ofstream file("customers.txt");
    for (int i = 0; i < count; i++)
        file << customers[i]->getCNIC() << "|"
             << customers[i]->getPassword() << "|"
             << customers[i]->getFullName() << "|M|000|City|"
             << (customers[i]->getIsBlocked() ? "1" : "0") << endl;
    file.close();
}

void FileManager::loadCatalog()
{
    ifstream file("catalog.txt");
    string line;
    cout << "Filter Catalog" << endl;
    while (getline(file, line))
        cout << line << endl;
    file.close();
}

void FileManager::saveCatalog(int filterID, bool status)
{
    ifstream file("catalog.txt");
    int lineCount = 0;
    string line;
    while (getline(file, line))
        lineCount++;

    file.clear();
    file.seekg(0);

    string *lines = new string[lineCount];
    for (int i = 0; i < lineCount; i++)
    {
        getline(file, lines[i]);
        if (!lines[i].empty() && lines[i].find(to_string(filterID) + "|") == 0)
            lines[i].back() = status ? '1' : '0';
    }
    file.close();

    ofstream outFile("catalog.txt");
    for (int i = 0; i < lineCount; i++)
        outFile << lines[i] << endl;
    delete[] lines;
}

void FileManager::appendSession(string cnic, string filterNames, string outPath)
{
    ofstream file("sessions.txt", ios::app);
    file << cnic << "|timestamp|" << filterNames << "|" << outPath << endl;
    file.close();
}

void FileManager::viewAllSessions()
{
    ifstream file("sessions.txt");
    string line;
    while (getline(file, line))
        cout << line << endl;
    file.close();
}
