#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <string>

using namespace std;

class Shape
{
	public:
		Shape();
		string getName();
	protected:
		string name;
};

#endif // __SHAPE_H__
