#include "Employee.h"
#include <iomanip>

void Employee::DisplayRecord()
{
	std::cout << std::left << std::setw(6) << "Name: " << std::left << std::setw(50) << GetName() << "\tSalary: " << mSalary << std::endl;
}
