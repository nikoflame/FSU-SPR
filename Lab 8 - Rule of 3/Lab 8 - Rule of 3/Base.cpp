#include "Base.h"
#include "Helper.h"

void Base::SetName(char* _name)
{
	Helper::CopyString(_name, mName);
}

Base& Base::operator=(Base& _other)
{
	if (this != &_other)
	{
		SetName(_other.mName);
	}
	return *this;
}

Base::Base(Base& _other)
{
	*this = _other;
}

Base::~Base()
{
	delete[] mName;
}
