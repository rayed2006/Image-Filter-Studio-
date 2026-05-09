#include "Customer.h"
#include "FileManager.h"
#include "FilterSession.h"
#include "Filter.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

Customer::Customer(string c, string p, string f, bool b) : User(c, p, f), isBlocked(b) {}

bool Customer::login(string c, string p)
{
    if (isBlocked)
    {
        cout << "Account is blocked." << endl;
        return false;
    }
    return (CNIC == c && password == p);
}

void Customer::registUser()
{
    ofstream f("customers.txt", ios::app);
    f << CNIC << "|" << password << "|" << fullName << "|M|000|City|0" << endl;
    f.close();
}

void Customer::viewHistory()
{
    ifstream f("sessions.txt");
    string line;
    bool found = false;
    cout << "Your Session History" << endl;
    while (getline(f, line))
    {
        if (line.find(CNIC) != string::npos)
        {
            cout << line << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No sessions found." << endl;
    f.close();
}

void Customer::loadAndApply()
{
    cout << "\n1. Load from file\n2. Generate test pattern\nChoice: ";
    int ch;
    cin >> ch;

    Image *img = nullptr;

    if (ch == 1)
    {
        cout << "Enter image path: ";
        string path;
        cin >> path;
        img = FileManager::loadSTB(path);
        if (!img)
            return;
        cout << "Image loaded: " << img->getWidth() << " x " << img->getHeight() << endl;
    }
    else
    {
        img = new Image(40, 20);
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 40; j++)
            {
                img->at(i, j).setR((i * 12) % 256);
                img->at(i, j).setG((j * 6) % 256);
                img->at(i, j).setB(((i + j) * 5) % 256);
            }
        cout << "Test pattern generated (40x20)." << endl;
    }

    cout << "\n=== ASCII Preview ===" << endl;
    img->displayASCII();

    FilterSession session;
    string pipelineDesc = "";
    bool done = false;

    while (!done)
    {
        cout << "Build Filter Pipeline" << endl;
        cout << "1.Grayscale  2.Invert  3.Brightness  4.ContrastStretch" << endl;
        cout << "5.RedChannel 6.GreenChannel 7.BlueChannel 8.BoxBlur" << endl;
        cout << "9.FlipHorizontal 10.FlipVertical 0.Done" << endl;
        cout << "Choice: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            session.addFilter(new Grayscale());
            pipelineDesc += "Grayscale>";
            break;
        case 2:
            session.addFilter(new Invert());
            pipelineDesc += "Invert>";
            break;
        case 3:
        {
            int v;
            cout << "Brightness value (-100 to 100): ";
            cin >> v;
            session.addFilter(new BrightnessAdjust(v));
            pipelineDesc += "Brightness>";
            break;
        }
        case 4:
            session.addFilter(new ContrastStretch());
            pipelineDesc += "ContrastStretch>";
            break;
        case 5:
            session.addFilter(new RedChannel());
            pipelineDesc += "RedChannel>";
            break;
        case 6:
            session.addFilter(new GreenChannel());
            pipelineDesc += "GreenChannel>";
            break;
        case 7:
            session.addFilter(new BlueChannel());
            pipelineDesc += "BlueChannel>";
            break;
        case 8:
            session.addFilter(new BoxBlur());
            pipelineDesc += "BoxBlur>";
            break;
        case 9:
            session.addFilter(new FlipHorizontal());
            pipelineDesc += "FlipHorizontal>";
            break;
        case 10:
            session.addFilter(new FlipVertical());
            pipelineDesc += "FlipVertical>";
            break;
        case 0:
            done = true;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }

    cout << "Applying Pipeline" << endl;
    session.runPipeline(*img);
    img->displayASCII();

    cout << "Save result? (y/n): ";
    char ans;
    cin >> ans;
    if (ans == 'y' || ans == 'Y')
    {
        time_t now = time(nullptr);
        char ts[32];
        strftime(ts, sizeof(ts), "%Y%m%d_%H%M%S", localtime(&now));
        string outPath = CNIC + "_" + ts + ".png";
        FileManager::saveSTB(outPath, img);
        FileManager::appendSession(CNIC, pipelineDesc, outPath);
        cout << "Saved to: " << outPath << endl;
        cout << "Session recorded." << endl;
    }

    delete img;
}
