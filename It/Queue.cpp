#include "Queue.h"

Queue::Queue()
{
	_size = 0;
}

Queue::~Queue()
{
	
}

void Queue::append(int value)
{
	_array[_size++] = value;
}

It* Queue::createIterator()
{
	It* it = new It();
	it -> _ptr = _array;
	it -> _ptrend = _array + _size;
	return it;
}