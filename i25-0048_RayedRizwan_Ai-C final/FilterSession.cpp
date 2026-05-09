#include "FilterSession.h"

FilterSession::FilterSession() : numFilters(0), capacity(20)
{
    pipeline = new Filter *[capacity];
}

FilterSession::~FilterSession()
{
    for (int i = 0; i < numFilters; i++)
        delete pipeline[i];
    delete[] pipeline;
}

FilterSession &FilterSession::addFilter(Filter *f)
{
    if (numFilters < capacity)
        pipeline[numFilters++] = f;
    return *this;
}

void FilterSession::runPipeline(Image &img)
{
    for (int i = 0; i < numFilters; i++)
        pipeline[i]->apply(img);
}
