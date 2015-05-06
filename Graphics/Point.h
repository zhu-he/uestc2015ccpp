#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point();
        Point(int x, int y);
        int getX();
        int getY();
        void move(int deltaX, int deltaY);
    protected:
        int x;
        int y;
};

#endif // POINT_H
