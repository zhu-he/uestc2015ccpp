#include "BigDecimal.h"

BigDecimal::BigDecimal(const int& delta, const int& divisor, const int& scale) : scale(scale)
{
	arraySize = scale / ratio + 2;
	array = new unsigned int[arraySize];
	int bigDelta = delta >> 5;
	int smallDelta = delta & ((1 << 5) - 1);
	for (int i = 0; i < bigDelta && i < arraySize; ++i)
	{
		array[i] = 0;
	}
	long long remain = 1LL << (32 - smallDelta);
	for (int i = bigDelta; i < arraySize; ++i)
	{
		array[i] = remain / divisor;
		remain = remain - array[i] * divisor;
		remain <<= 32;
	}
}

BigDecimal::~BigDecimal()
{
	delete array;
}

void BigDecimal::operator += (const BigDecimal& bigDecimal)
{
	int remain = 0;
	for (int i = arraySize - 1; i >= 0; --i)
	{
		long long tmp = (long long)array[i] + bigDecimal.array[i] + remain;
		array[i] = tmp & ((1LL << 32) - 1);
		remain = tmp >> 32;
	}
}

void BigDecimal::operator -= (const BigDecimal& bigDecimal)
{
	int remain = 0;
	for (int i = arraySize - 1; i >= 0; --i)
	{
		long long tmp = (long long)array[i] - bigDecimal.array[i] + remain;
		array[i] = tmp & ((1LL << 32) - 1);
		remain = tmp >> 32;
	}
}

std::ostream& operator << (std::ostream& out, const BigDecimal& bigDecimal)
{
	out << bigDecimal.array[0] << ".";
	unsigned int tmpArray[bigDecimal.arraySize];
	memcpy(tmpArray, bigDecimal.array, sizeof(tmpArray));
	for (int i = 0; i < bigDecimal.scale; ++i)
	{
		int remain = 0;
		for (int j = bigDecimal.arraySize - 1; j >= 1; --j)
		{
			long long tmp = tmpArray[j] * 10LL + remain;
			tmpArray[j] = tmp & ((1LL << 32) - 1);
			remain = tmp >> 32;
		}
		out << remain;
	}
	return out;
}