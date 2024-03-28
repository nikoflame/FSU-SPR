#include <iostream>
#include "TriangleHeap.h"
#include "TriangleStack.h"
#include <vector>

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

//declarations
int AddNumbersReturnInt(int* a, int* b);
void AddNumbersReturnVoid(int a, int b, int* sum);
void SwapValues(int* a, int* b);

int main()
{
    //---------- Memory Leak Detection Code ----------//
    // Put this block at the top of main in order to turn on memory leak detection
    ENABLE_LEAK_DETECTION(); //will do nothing if NOT a debug build

    // Important! Start this parameter off at -1, but change it to the allocation number to track down any leaks!
    _CrtSetBreakAlloc(-1);
    //---------- Memory Leak Detection Code ----------//

    //declare two TriangleStack variables
    TriangleStack a, b;

    //set their members to whatever two different values you want
    a.SetBase(2.0f);
    a.SetHeight(3.0f);
    b.SetBase(2.5f);
    b.SetHeight(3.5f);

    //declare a vector<TriangleStack>
    std::vector<TriangleStack> v;

    //add the two triangles to it using its .push_back() method
    v.push_back(a);
    v.push_back(b);

    //loop through the vector and print each triangle’s area to the screen
    std::cout << "----- TriangleStack -----" << std::endl;
    for (int i = 0; i < v.size(); i++)
        std::cout << "Area of triangle " << i+1 << ": " << v[i].GetArea() << std::endl;

    //----------------- Repeat this process again but use TriangleHeap instead -----------------

    //declare two TriangleHeap variables
    TriangleHeap c, d;

    //set their members to whatever two different values you want
    c.SetBase(2.0f);
    c.SetHeight(3.0f);
    d.SetBase(2.5f);
    d.SetHeight(3.5f);

    //declare a vector<TriangleHeap>
    std::vector<TriangleHeap> v2;

    //add the two triangles to it using its .push_back() method
    v2.push_back(c);
    v2.push_back(d);

    //loop through the vector and print each triangle’s area to the screen
    std::cout << "\n----- TriangleHeap -----" << std::endl;
    for (int i = 0; i < v2.size(); i++)
        std::cout << "Area of triangle " << i + 1 << ": " << v2[i].GetArea() << std::endl;

    //let me see what's happening
    system("pause");

    //exit gracefully
    return 0;
}

//definitions
int AddNumbersReturnInt(int* a, int* b)
{
    return *a + *b; //dereference pointers, add, and return the int
}

void AddNumbersReturnVoid(int a, int b, int* sum)
{
    *sum = a + b; //dereference sum and assign the sum of a and b to it;
}

void SwapValues(int* a, int* b)
{
    int temp = *a; //give value of 'a' to placeholder
    *a = *b; //assign value of 'b' to 'a' 
    *b = temp; //assign value of placeholer to 'b'
}