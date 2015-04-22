#ifndef __SAFE_ARRAY_H__
#define __SAFE_ARRAY_H__

#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

template <class T>
class SafeArray
{
public:
	SafeArray(int size);
	SafeArray(int size, T value);
	~SafeArray();
	T& operator [] (const int& index);
	template <class sT>
	friend ostream& operator << (ostream& out, const SafeArray<sT>& safeArray);
private:
	T *_array;
	int _size;
};

#include "SafeArray.cpp"

#endif
