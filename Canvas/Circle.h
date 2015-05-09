#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Shape.h"

class Circle : public Shape
{
	public:
		Circle(int x, int y, int radius);
	private:
		int x;
		int y;
		int radius;
};

#endif // __CIRCLE_H__
