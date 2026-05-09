#include "Filter.h"

void Grayscale::apply(Image &img)
{
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
        {
            int g = (img.at(i, j).getR() + img.at(i, j).getG() + img.at(i, j).getB()) / 3;
            img.at(i, j).setR(g);
            img.at(i, j).setG(g);
            img.at(i, j).setB(g);
        }
}

void Invert::apply(Image &img)
{
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
        {
            img.at(i, j).setR(255 - img.at(i, j).getR());
            img.at(i, j).setG(255 - img.at(i, j).getG());
            img.at(i, j).setB(255 - img.at(i, j).getB());
        }
}

BrightnessAdjust::BrightnessAdjust(int val) : v(val) {}

void BrightnessAdjust::apply(Image &img)
{
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
        {
            img.at(i, j).setR(img.at(i, j).getR() + v);
            img.at(i, j).setG(img.at(i, j).getG() + v);
            img.at(i, j).setB(img.at(i, j).getB() + v);
        }
}

void ContrastStretch::apply(Image &img)
{
    int mi = 255, ma = 0;
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
        {
            int r = img.at(i, j).getR();
            int g = img.at(i, j).getG();
            int b = img.at(i, j).getB();
            if (r < mi) mi = r;
            if (g < mi) mi = g;
            if (b < mi) mi = b;
            if (r > ma) ma = r;
            if (g > ma) ma = g;
            if (b > ma) ma = b;
        }
    if (ma <= mi) return;
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
        {
            Pixel &p = img.at(i, j);
            p.setR((p.getR() - mi) * 255 / (ma - mi));
            p.setG((p.getG() - mi) * 255 / (ma - mi));
            p.setB((p.getB() - mi) * 255 / (ma - mi));
        }
}

void RedChannel::apply(Image &img)
{
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
        {
            img.at(i, j).setG(0);
            img.at(i, j).setB(0);
        }
}

void GreenChannel::apply(Image &img)
{
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
        {
            img.at(i, j).setR(0);
            img.at(i, j).setB(0);
        }
}

void BlueChannel::apply(Image &img)
{
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
        {
            img.at(i, j).setR(0);
            img.at(i, j).setG(0);
        }
}

void BoxBlur::apply(Image &img)
{
    Image copy(img);
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
        {
            int r = 0, g = 0, b = 0, count = 0;
            for (int dy = -1; dy <= 1; dy++)
                for (int dx = -1; dx <= 1; dx++)
                {
                    int ni = i + dy, nj = j + dx;
                    if (ni >= 0 && ni < img.getHeight() && nj >= 0 && nj < img.getWidth())
                    {
                        r += copy.at(ni, nj).getR();
                        g += copy.at(ni, nj).getG();
                        b += copy.at(ni, nj).getB();
                        count++;
                    }
                }
            img.at(i, j).setR(r / count);
            img.at(i, j).setG(g / count);
            img.at(i, j).setB(b / count);
        }
}

void FlipHorizontal::apply(Image &img)
{
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth() / 2; j++)
        {
            Pixel tmp = img.at(i, j);
            img.at(i, j) = img.at(i, img.getWidth() - 1 - j);
            img.at(i, img.getWidth() - 1 - j) = tmp;
        }
}

void FlipVertical::apply(Image &img)
{
    for (int i = 0; i < img.getHeight() / 2; i++)
        for (int j = 0; j < img.getWidth(); j++)
        {
            Pixel tmp = img.at(i, j);
            img.at(i, j) = img.at(img.getHeight() - 1 - i, j);
            img.at(img.getHeight() - 1 - i, j) = tmp;
        }
}
