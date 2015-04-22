#include "SafeArray.h"

template <class T>
SafeArray<T>::SafeArray(int size)
{
	_size = size;
	_array = (T*) malloc(size * sizeof(T));
}

template <class T>
SafeArray<T>::SafeArray(int size, T value)
{
	_size = size;
	_array = (T*) malloc(size * sizeof(T));
	for (int i = 0; i < size; ++i)
	{
		_array[i] = value;
	}
}

template <class T>
SafeArray<T>::~SafeArray()
{
	delete[] _array;
}

template <class T>
T& SafeArray<T>::operator [] (const int& index)
{
	assert(index >= 0 && index < _size);
	return _array[index];
}

template <class T>
ostream& operator << (ostream& out, const SafeArray<T>& safeArray)
{
	out << '[';
	for (int i = 0; i < safeArray._size; ++i)
	{
		if (i > 0)
		{
			out << ',';
		}
		out << safeArray._array[i];
	}
	return out << "]\n";
}
