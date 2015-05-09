#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "Shape.h"
#include <iostream>
#include <vector>

using namespace std;

class Canvas
{
	public:
		Canvas();
		void append(Shape *shape);
		void draw();
	private:
		vector<Shape*> shapes;
};

#endif // __CANVAS_H__
