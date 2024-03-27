#include <vector>
#include "Employee.h"
#include "Student.h"
#include "Helper.h"

//---------- Memory Leak Detection Code ----------//
// Need this block for memory leak detection
#if defined _MSC_VER && defined _DEBUG
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define ENABLE_LEAK_DETECTION() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define ENABLE_LEAK_DETECTION()
#endif
//---------- Memory Leak Detection Code ----------//

//declare functions here
void AddRecord(std::vector<Base*>& _v);
void DisplayRecords(std::vector<Base*>& _v);
void DuplicateRecord(std::vector<Base*>& _v);

int main()
{
    //---------- Memory Leak Detection Code ----------//
    // Put this block at the top of main in order to turn on memory leak detection
    ENABLE_LEAK_DETECTION(); //will do nothing if NOT a debug build

    // Important! Start this parameter off at -1, but change it to the allocation number to track down any leaks!
    _CrtSetBreakAlloc(-1);
    //---------- Memory Leak Detection Code ----------//

    //declare a vector of base pointers
    std::vector<Base*> v;

    //create a menu loop that will allow the user to add a record, display all records, duplicate a record, or exit the menu loop
    std::string menuRecords[4] =
    {
        "Add a record",
        "Display all records",
        "Duplicate a record",
        "Exit"
    };
    int choiceRecords = Helper::MenuAndChoice("Records Menu: ", menuRecords, 4);

    //clear screen for selection
    system("cls");

    //switch for records menu
    bool exit = false;
    do
    {
        switch (choiceRecords)
        {
            case 1:
            {
                AddRecord(v);
                break;
            }
            case 2:
            {
                DisplayRecords(v);
                break;
            }
            case 3:
            {
                DuplicateRecord(v);
                break;
            }
            case 4:
            default:
            {
                exit = true;
                break;
            }
        }
    } while (!exit);

    //delete all records in the vector at the end of main
    for (auto ptr : v)
        delete ptr;

    //exit gracefully
    return 0;
}

//define funtions here
void AddRecord(std::vector<Base*>& _v)
{
    //Ask the user which type of record they want to add, an employee or a student
    std::string menuTypes[2] =
    {
        "Employee",
        "Student"
    };
    int choiceTypes = Helper::MenuAndChoice("Which type of record would you like to add? ", menuTypes, 2);

    //dynamically create a new pointer of the selected type of record
    //and have them fill out the record’s members via its Set methods
    //then add it to the vector using the vector method .push_back()
    if (choiceTypes == 1)
    {
        //new pointer
        Employee* rec = new Employee();

        //set name
        std::cout << "What is their name? -> ";
        char* _name = new char[100];
        std::cin >> _name;
        rec->SetName(_name);
        delete[] _name;

        //set salary
        std::cout << "What is their salary? -> ";
        int _salary;
        std::cin >> _salary;
        rec->SetSalary(_salary);

        //add to vector
        _v.push_back(rec);
    }
    else
    {
        //new pointer
        Student* rec = new Student();

        //set name
        std::cout << "What is their name? -> ";
        char* _name = new char[100];
        std::cin >> _name;
        rec->SetName(_name);
        delete[] _name;

        //set GPA
        std::cout << "What is their GPA? -> ";
        int _GPA;
        std::cin >> _GPA;
        rec->SetGPA(_GPA);

        //add to vector
        _v.push_back(rec);
    }
}

void DisplayRecords(std::vector<Base*>& _v)
{
    for (auto rec : _v)
        rec->DisplayRecord();
}

void DuplicateRecord(std::vector<Base*>& _v)
{
    int index = Helper::GetValidatedInt("Enter the index of the record to create a copy from the vector of records: ", 0, _v.size() - 1);

    if (dynamic_cast<Student*>(_v[index]))
    {
        Student* original = dynamic_cast<Student*>(_v[index]);
        Student* copy = new Student(*original);
        _v.push_back(copy);
    }
    else
    {
        Employee* original = dynamic_cast<Employee*>(_v[index]);
        Employee* copy = new Employee(*original);
        _v.push_back(copy);
    }
}