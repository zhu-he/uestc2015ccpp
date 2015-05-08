#ifndef __BIG_DECIMAL__
#define __BIG_DECIMAL__

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

class BigDecimal
{
public:
	BigDecimal(int dividend, int divisor, int scale);
	~BigDecimal();
	int compareAbsTo(const BigDecimal& bigDecimal);
	bool isZero();
	void operator += (const BigDecimal& bigDecimal);
	void operator -= (const BigDecimal& bigDecimal);
	void operator >>= (const int& delta);
	friend std::ostream& operator << (std::ostream& out, const BigDecimal& bigDecimal);
private:
	unsigned int* array;
	bool sign;
	int scale;
	int arraySize;
};

#endif // __BIG_DECIMAL__