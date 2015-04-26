#include "It.h"

It::It()
{

}

It::~It()
{

}

int* It::next()
{
	if (_ptr == _ptrend)
	{
		return NULL;
	}
	return _ptr++;
}