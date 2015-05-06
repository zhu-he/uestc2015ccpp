#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

class Circle : private Point
{
    public:
        Circle(Point center, int radius);
        Point getCenter();
        void move(int deltaX, int deltaY);
    protected:
        int radius;
};

#endif // CIRCLE_H
