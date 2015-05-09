#ifndef __BIG_DECIMAL__
#define __BIG_DECIMAL__

#include <iostream>
#include <cstring>
#include <cmath>

const float ratio = 32 * log10(2);

class BigDecimal
{
public:
	BigDecimal(const int& delta, const int& divisor, const int& scale);
	~BigDecimal();
	void operator += (const BigDecimal& bigDecimal);
	void operator -= (const BigDecimal& bigDecimal);
	friend std::ostream& operator << (std::ostream& out, const BigDecimal& bigDecimal);
private:
	unsigned int* array;
	int scale;
	int arraySize;
	int bigDelta;
};

#endif // __BIG_DECIMAL__