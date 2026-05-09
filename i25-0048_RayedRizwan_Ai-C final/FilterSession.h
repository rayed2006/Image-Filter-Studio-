#pragma once
#include "Filter.h"

class FilterSession {
private:
    Filter **pipeline;
    int numFilters, capacity;

public:
    FilterSession();
    ~FilterSession();
    FilterSession &addFilter(Filter *f);
    void runPipeline(Image &img);
};
