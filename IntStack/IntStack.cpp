#include "IntStack.h"

IntStack::IntStack()
{
	_size = 0;
	headNode = new Node();
	rearNode = headNode;
	headNode->previous = 0;
	headNode->next = 0;
}

IntStack::~IntStack()
{
	Node *pNode = headNode;
	while (pNode->next)
	{
		pNode = pNode->next;
		delete pNode->previous;
	}
	delete pNode;
}

void IntStack::push(int value)
{
	Node *newNode = new Node();
	newNode->value = value;
	newNode->previous = rearNode;
	newNode->next = 0;
	rearNode = newNode;
	_size++;
}

void IntStack::pop()
{
	Node *newNode = rearNode->previous;
	delete rearNode;
	newNode->next = 0;
	rearNode = newNode;
	_size--;
}

int IntStack::top()
{
	return rearNode->value;
}

bool IntStack::empty()
{
	return _size == 0;
}

unsigned int IntStack::size()
{
	return _size;
}
