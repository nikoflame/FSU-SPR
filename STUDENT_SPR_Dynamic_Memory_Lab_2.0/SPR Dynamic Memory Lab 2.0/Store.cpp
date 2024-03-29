#include "Store.h"

Store::Store()
{
	//Item* helperItem = new Item("DEFAULT", 10);
	m_Inventories = new Inventory[m_NumInventories];
}

void Store::Print() const
{
	for (unsigned int i = 0; i < m_NumInventories; ++i)
	{
		m_Inventories[i].Print();
	}
}

Store::~Store()
{
	delete[] m_Inventories;
}

//void Store::CleanUp()
//{
//	this->m_Inventories->CleanUp();
//	delete[] m_Inventories;
//}
