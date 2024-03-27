#pragma once

#include <iostream>
#define TH template<typename Type>

template<typename Type = int>
class DList
{
private:

	struct node
	{
		node* next, *prev;
		Type data;

		node(Type& _data, node* _prev) : data(_data), prev(_prev), next(nullptr) {}
	};

	int count;
	node* first, *last;

public:
	DList() { first = last = nullptr; count = 0; }
	~DList();

	int GetCount() { return count; }

	void push_back(Type _data);

	Type& operator[](int _index);
	const Type& operator[](int _index) const;

	// my code
	void Clear();
	void Push_Front(Type _data);
	void Erase(const unsigned int index);
};



TH
void DList<Type>::push_back(Type _data)
{
	node* n = new node(_data, last);

	if (last)
		last->next = n;
	else
		first = n;

	last = n;

	++count;
}

template<typename Type>
DList<Type>::~DList()
{
	//You will need to fill this out
	Clear();
}

template<typename Type>
Type& DList<Type>::operator[](int _index)
{
	node* temp = first;

	int i = 0;
	for (; i < _index; ++i)
		temp = temp->next;

	return temp->data;
}

template<typename Type>
const Type& DList<Type>::operator[](int _index) const
{
	node* temp = first;

	int i = 0;
	for (; i < _index; ++i)
		temp = temp->next;

	return temp->data;
}

// my code
void DList<Type>::Clear()
{
	// start at the beginning
	node* thisNode = first;

	//check if the currently accessed node is real or not
	while (thisNode != nullptr)
	{
		//make a variable for the next node
		node* thatNode = thisNode->next;

		//delete the currently accessed node
		delete thisNode;

		//go to the next node
		thisNode = thatNode;
	}

	//do the same stuff the default constructor does
	first = last = nullptr;
	count = 0;
}

void DList<Type>::Push_Front(Type _data)
{
	//make a new node, and make sure the previous node is a nullptr since this new one will be the first
	node* n = new node(_data, nullptr);

	if (first) //if first node exists
	{
		n->next = first; //set the next node of the new node to the old first node
		first->prev = n; //add new node to the spot before the first node
		first = n; //make the new node the first node
	}
	else //else if there is no first node, then the list is empty
		first = last = n; //make the first and last node the new node

	//increase size of DList
	++count;

}

void DList<Type>::Erase(const unsigned int index)
{
	//if the index does not exist, do nothing.
	if (index >= count)
		return;

	//target the first node
	node* n = first;

	//if the index isn't trying to erase the first node, move the pointer to the correct node
	for (int i = 0; i < index; i++)
		n = n->next;

	//by now, the correct node has been targeted and is pointed to by 'n'

	//if the node is the only node, clear the list
	if (first == last)
		Clear();
	
	//if the node is not the only node
	else
	{
		//if the node is first, make the next node's prev pointer point to a nullptr
		if (first == n)
			n->next->prev = nullptr;

		//if the node is last, make the prev node's next pointer point to a nullptr
		else if (last == n)
			n->prev->next = nullptr;

		//if the node is neither first or last, then it is in the middle
		else
		{
			//make the prev node's next pointer point to the next node instead of n
			n->prev->next = n->next;
			//make the next node's prev pointer point to the prev node instead of n
			n->next->prev = n->prev;
		}

		//finally, delete the node and update the count
		delete n;
		count--;
	}
}