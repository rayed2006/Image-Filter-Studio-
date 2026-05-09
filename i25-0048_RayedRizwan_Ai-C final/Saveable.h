#pragma once
#include <string>
using namespace std;

class Saveable
{
public:
    virtual void save(string path) = 0;
    virtual ~Saveable() {}
};
