#pragma once
#include "Item.h"
#include <vector>
#include <iostream>
#include <string>

class Inventory
{
	std::vector<Item*> m_Items;
	static unsigned int m_ItemsMade;

	void CreateItem()
	{
		std::string name = "Item " + std::to_string(m_ItemsMade);
		m_Items.push_back(new Item(name.c_str(), 100 * m_ItemsMade));
		++m_ItemsMade;
	}

public:
	Inventory()
	{
		CreateItem();
		CreateItem();
		CreateItem();
	}

	void Print() const
	{
		size_t* nSize = new size_t(m_Items.size());
		std::cout << "_____INVENTORY_____\n";
		for (unsigned int i = 0; i < *nSize; ++i)
		{
			m_Items[i]->Print();
		}
		delete nSize;
	}

	//void CleanUp()
	//{
	//	for (int i = 0; i < m_Items.size(); i++)
	//	{
	//		this->m_Items[i]->CleanUp();
	//		delete m_Items[i];
	//	}
	//}

	~Inventory()
	{
		for (int i = 0; i < m_Items.size(); i++)
		{
			delete m_Items[i];
		}
	}
};