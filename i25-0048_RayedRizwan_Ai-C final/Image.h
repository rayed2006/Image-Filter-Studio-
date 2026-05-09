#pragma once
#include "Pixel.h"
#include "Saveable.h"
#include "Previewable.h"
using namespace std;

class FilterSession;

class Image : public Saveable, public Previewable {
private:
    Pixel **grid;
    int width;
    int height;

public:
    Image();
    Image(int w, int h);
    Image(const Image &other);
    ~Image();
    Image &operator=(const Image &other);
    int getWidth() const;
    int getHeight() const;
    Pixel &at(int row, int col);
    void save(string path) override;
    void displayASCII() override;
    friend class FilterSession;
};
