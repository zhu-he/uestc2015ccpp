#ifndef __RECT_H__
#define __RECT_H__

#include "Shape.h"

class Rect : public Shape
{
	public:
		Rect(int x, int y, int height, int width);
	private:
		int x;
		int y;
		int height;
		int width;
};

#endif // __RECT_H__
