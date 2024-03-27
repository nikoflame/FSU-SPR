#include "Student.h"
#include <iomanip>

void Student::DisplayRecord()
{
	std::cout << std::left << std::setw(6) << "Name: " << std::left << std::setw(50) << GetName() << "\tGPA: " << mGPA << std::endl;
}
