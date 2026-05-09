#include "Pixel.h"

Pixel::Pixel() : r(0), g(0), b(0) {}

Pixel::Pixel(int r, int g, int b) : r(clamp(r)), g(clamp(g)), b(clamp(b)) {}

int Pixel::clamp(int val)
{
    if (val < 0)
        return 0;
    if (val > 255)
        return 255;
    return val;
}

int Pixel::getR() const { return r; }
int Pixel::getG() const { return g; }
int Pixel::getB() const { return b; }

void Pixel::setR(int r) { this->r = clamp(r); }
void Pixel::setG(int g) { this->g = clamp(g); }
void Pixel::setB(int b) { this->b = clamp(b); }

Pixel Pixel::operator+(const Pixel &other) const
{
    return Pixel(r + other.r, g + other.g, b + other.b);
}

ostream &operator<<(ostream &os, const Pixel &p)
{
    int avg = (p.r + p.g + p.b) / 3;
    const char map[] = {' ', '.', ':', '-', '=', '+', '*', '#', '@'};
    int index = (avg * 8) / 255;
    os << map[index];
    return os;
}
