#pragma once
#include "Image.h"

class Filter {
public:
    virtual void apply(Image &img) = 0;
    virtual ~Filter() {}
};

class Grayscale : public Filter {
public:
    void apply(Image &img) override;
};

class Invert : public Filter {
public:
    void apply(Image &img) override;
};

class BrightnessAdjust : public Filter {
    int v;
public:
    BrightnessAdjust(int val);
    void apply(Image &img) override;
    int getVal() const { return v; }
};

class ContrastStretch : public Filter {
public:
    void apply(Image &img) override;
};

class RedChannel : public Filter {
public:
    void apply(Image &img) override;
};

class GreenChannel : public Filter {
public:
    void apply(Image &img) override;
};

class BlueChannel : public Filter {
public:
    void apply(Image &img) override;
};

class BoxBlur : public Filter {
public:
    void apply(Image &img) override;
};

class FlipHorizontal : public Filter {
public:
    void apply(Image &img) override;
};

class FlipVertical : public Filter {
public:
    void apply(Image &img) override;
};
