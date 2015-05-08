#ifndef __BIG_DECIMAL__
#define __BIG_DECIMAL__

#include <iostream>
#include <cstring>
#include <cmath>

const float ratio = 32 * log10(2);

class BigDecimal
{
public:
	BigDecimal(const int& dividend, const int& divisor, const int& scale);
	~BigDecimal();
	void operator += (const BigDecimal& bigDecimal);
	void operator -= (const BigDecimal& bigDecimal);
	void operator >>= (const int& delta);
	friend std::ostream& operator << (std::ostream& out, const BigDecimal& bigDecimal);
private:
	unsigned int* array;
	int scale;
	int arraySize;
};

#endif // __BIG_DECIMAL__