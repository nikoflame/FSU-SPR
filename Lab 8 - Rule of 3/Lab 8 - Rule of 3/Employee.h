#pragma once
#include "Base.h"

class Employee :
    public Base
{
private:
    int mSalary;

public:
    void SetSalary(int _salary) { mSalary = _salary; }

    void DisplayRecord();
};

