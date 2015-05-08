#ifndef __BIG_DECIMAL__
#define __BIG_DECIMAL__

#include <iostream>
#include <cmath>

class BigDecimal
{
public:
	BigDecimal(int dividend, int divisor, int scale);
	int compareAbsTo(const BigDecimal& bigDecimal);
	friend BigDecimal operator - (BigDecimal bigDecimal);
	friend BigDecimal operator + (BigDecimal bigDecimal1, const BigDecimal& bigDecimal2);
	friend BigDecimal operator - (BigDecimal bigDecimal1, const BigDecimal& bigDecimal2);
	friend BigDecimal operator >> (BigDecimal bigDecimal, const int& delta);
	friend std::ostream& operator << (std::ostream& out, BigDecimal bigDecimal);
private:
	unsigned int array[10000];
	bool sign;
	int scale;
	int arraySize;
};

#endif // __BIG_DECIMAL__