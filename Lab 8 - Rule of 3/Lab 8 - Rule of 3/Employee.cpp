#include "Employee.h"

void Employee::DisplayRecord()
{
	std::cout << "Name: " << GetName() << "\tSalary: " << mSalary << std::endl;
}
