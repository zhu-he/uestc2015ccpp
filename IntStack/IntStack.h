#ifndef __INT_STACK__
#define __INT_STACK__

class IntStack
{
private:
	struct Node
	{
		int value;
		Node *previous;
		Node *next;
	};
	Node *headNode;
	Node *rearNode;
	unsigned int _size;
public:
	IntStack();
	~IntStack();
	void push(int num);
	void pop();
	int top();
	bool empty();
	unsigned int size();
};

#include "IntStack.cpp"

#endif