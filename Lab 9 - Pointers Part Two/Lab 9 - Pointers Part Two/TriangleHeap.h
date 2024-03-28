#pragma once

class TriangleHeap {
private:
    float* mBase;
    float* mHeight;

public:
    TriangleHeap() //new default constructor
        : mBase(new float(1.0f)), mHeight(new float(1.0f)) {}

    //rule of 3
    TriangleHeap(const TriangleHeap& other) //copy constructor
        : mBase(new float(*other.mBase)), mHeight(new float(*other.mHeight)) {} //better than code
    TriangleHeap& operator=(const TriangleHeap& other); //assignment operator
    ~TriangleHeap(); //destructor

    void SetBase(float base);
    void SetHeight(float height);
    float GetArea();
};
