#pragma once
#include <iostream>

class Base
{
private:
	char* mName = nullptr;

public:
	Base() {} //new empty default constructor

	void SetName(char* _name);
	char* GetName() { return mName; }

	virtual void DisplayRecord() = 0;

	//rule of 3
	Base& operator=(Base& _other); //assignment operator
	Base(Base& _other); //copy constructor
	~Base(); //destructor
};

