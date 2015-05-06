#include <iostream>
#include "Point.h"
#include "Circle.h"

using namespace std;

int main()
{
    Point center(10, 20);
    Circle circle(center, 5);
    circle.move(30, 20);
    cout << circle.getCenter().getX() << ":" << circle.getCenter().getY() << endl;
    return 0;
}
