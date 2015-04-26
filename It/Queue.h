#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "It.h"

class Queue
{
	static const int MAX = 100;
public:
	Queue();
	~Queue();
	void append(int value);
	It* createIterator();
private:
	int _size;
	int _array[MAX];
};

#include "Queue.cpp"

#endif
