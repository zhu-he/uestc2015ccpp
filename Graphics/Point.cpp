#include "Point.h"

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(int x, int y) : x(x), y(y)
{

}

int Point::getX()
{
    return x;
}

int Point::getY()
{
    return y;
}

void Point::move(int deltaX, int deltaY)
{
    x += deltaX;
    y += deltaY;
}
