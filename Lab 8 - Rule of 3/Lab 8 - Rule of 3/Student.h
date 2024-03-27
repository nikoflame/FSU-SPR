#pragma once
#include "Base.h"

class Student :
    public Base
{
private:
    float mGPA;

public:
    void SetGPA(float _GPA) { mGPA = _GPA; }

    void DisplayRecord();
};

