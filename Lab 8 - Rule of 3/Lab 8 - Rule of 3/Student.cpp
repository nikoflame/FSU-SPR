#include "Student.h"

void Student::DisplayRecord()
{
	std::cout << "Name: " << GetName() << "\tGPA: " << mGPA << std::endl;
}
