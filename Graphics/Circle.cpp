#include "Circle.h"

Circle::Circle(Point center, int radius)
{
    x = center.getX();
    y = center.getY();
}

void Circle::move(int deltaX, int deltaY)
{
    Point::move(deltaX, deltaY);
}

Point Circle::getCenter()
{
    return Point(x, y);
}
