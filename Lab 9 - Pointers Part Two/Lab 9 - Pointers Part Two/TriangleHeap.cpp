#include "TriangleHeap.h"

TriangleHeap& TriangleHeap::operator=(const TriangleHeap& other)
{
    if (this != &other) { //if they're not the same, assign the members
        *mBase = *other.mBase;
        *mHeight = *other.mHeight;
    }
    return *this; //compiler tells me i need a return
}

TriangleHeap::~TriangleHeap()
{
    delete mBase;
    delete mHeight;
}

void TriangleHeap::SetBase(float base)
{
    *mBase = base;
}

void TriangleHeap::SetHeight(float height)
{
    *mHeight = height;
}

float TriangleHeap::GetArea()
{
    return (*mBase * *mHeight) / 2.0f;
}
