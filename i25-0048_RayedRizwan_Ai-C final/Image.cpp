#include "Image.h"
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
using namespace std;

Image::Image() : grid(nullptr), width(0), height(0) {}

Image::Image(int w, int h) : width(w), height(h)
{
    grid = new Pixel *[height];
    for (int i = 0; i < height; i++)
        grid[i] = new Pixel[width];
}

Image::Image(const Image &other) : width(other.width), height(other.height)
{
    grid = new Pixel *[height];
    for (int i = 0; i < height; i++)
    {
        grid[i] = new Pixel[width];
        for (int j = 0; j < width; j++)
            grid[i][j] = other.grid[i][j];
    }
}

Image::~Image()
{
    if (grid)
    {
        for (int i = 0; i < height; i++)
            delete[] grid[i];
        delete[] grid;
    }
}

Image &Image::operator=(const Image &other)
{
    if (this != &other)
    {
        if (grid)
        {
            for (int i = 0; i < height; i++)
                delete[] grid[i];
            delete[] grid;
        }
        width = other.width;
        height = other.height;
        grid = new Pixel *[height];
        for (int i = 0; i < height; i++)
        {
            grid[i] = new Pixel[width];
            for (int j = 0; j < width; j++)
                grid[i][j] = other.grid[i][j];
        }
    }
    return *this;
}

int Image::getWidth() const { return width; }
int Image::getHeight() const { return height; }

Pixel &Image::at(int row, int col) { return grid[row][col]; }

void Image::save(string path)
{
    unsigned char *data = new unsigned char[width * height * 3];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            data[3 * (i * width + j) + 0] = grid[i][j].getR();
            data[3 * (i * width + j) + 1] = grid[i][j].getG();
            data[3 * (i * width + j) + 2] = grid[i][j].getB();
        }
    stbi_write_png(path.c_str(), width, height, 3, data, width * 3);
    delete[] data;
}

void Image::displayASCII()
{
    int rowStep = (height / 20 > 0) ? height / 20 : 1;
    int colStep = (width  / 40 > 0) ? width  / 40 : 1;
    for (int i = 0; i < height; i += rowStep)
    {
        for (int j = 0; j < width; j += colStep)
            cout << grid[i][j];
        cout << endl;
    }
}
