#include "Canvas.h"

Canvas::Canvas()
{
	
}

void Canvas::append(Shape *shape)
{
	shapes.push_back(shape);
}

void Canvas::draw()
{
	for (vector<Shape*>::iterator i = shapes.begin(); i != shapes.end(); ++i)
	{
		cout << (*i)->getName() << endl;
	}
}
