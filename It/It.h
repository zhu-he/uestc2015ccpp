#ifndef __IT_H__
#define __IT_H__

#include "Queue.h"

class It
{
public:
	It();
	~It();
	int* next();
	friend class Queue;
private:
	int* _ptr;
	int* _ptrend;
};

#include "It.cpp"

#endif