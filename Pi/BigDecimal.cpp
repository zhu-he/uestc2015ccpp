#include "BigDecimal.h"

BigDecimal::BigDecimal(int dividend, int divisor, int scale) : scale(scale)
{
	long long remain = dividend;
	sign = false;
	if (remain < 0)
	{
		remain = -remain;
		sign = true;
	}
	arraySize = scale / (32 * log10(2)) + 2;
	array = new unsigned int[arraySize];
	for (int i = 0; i < arraySize; ++i)
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

int BigDecimal::compareAbsTo(const BigDecimal& bigDecimal)
{
	for (int i = 0; i < arraySize; ++i)
	{
		if (array[i] > bigDecimal.array[i])
		{
			return 1;
		}
		if (array[i] < bigDecimal.array[i])
		{
			return -1;
		}
	}
	return 0;
}

bool BigDecimal::isZero()
{
	for (int i = arraySize - 1; i >= 0; --i)
	{
		if (array[i] > 0)
		{
			return false;
		}
	}
	return true;
}

void BigDecimal::operator += (const BigDecimal& bigDecimal)
{
	if (sign ^ bigDecimal.sign)
	{
		if (compareAbsTo(bigDecimal) >= 0)
		{
			int remain = 0;
			for (int i = arraySize - 1; i >= 0; --i)
			{
				long long tmp = (long long)array[i] - remain - bigDecimal.array[i];
				if (tmp < 0)
				{
					remain = 1;
					tmp += 1LL << 32;
				}
				else
				{
					remain = 0;
				}
				array[i] = tmp;
			}
		}
		else
		{
			int remain = 0;
			for (int i = arraySize - 1; i >= 0; --i)
			{
				long long tmp = (long long)bigDecimal.array[i] - remain - array[i];
				if (tmp < 0)
				{
					remain = 1;
					tmp += 1LL << 32;
				}
				else
				{
					remain = 0;
				}
				array[i] = tmp;
			}
			sign = !sign;
		}
	}
	else
	{
		int remain = 0;
		for (int i = arraySize - 1; i >= 0; --i)
		{
			long long tmp = (long long)array[i] + bigDecimal.array[i] + remain;
			array[i] = tmp & ((1LL << 32) - 1);
			remain = tmp >> 32;
		}
	}
}

void BigDecimal::operator -= (const BigDecimal& bigDecimal)
{
	if (sign ^ bigDecimal.sign)
	{
		int remain = 0;
		for (int i = arraySize - 1; i >= 0; --i)
		{
			long long tmp = (long long)array[i] + bigDecimal.array[i] + remain;
			array[i] = tmp & ((1LL << 32) - 1);
			remain = tmp >> 32;
		}
	}
	else
	{
		if (compareAbsTo(bigDecimal) >= 0)
		{
			int remain = 0;
			for (int i = arraySize - 1; i >= 0; --i)
			{
				long long tmp = (long long)array[i] - remain - bigDecimal.array[i];
				if (tmp < 0)
				{
					remain = 1;
					tmp += 1LL << 32;
				}
				else
				{
					remain = 0;
				}
				array[i] = tmp;
			}
		}
		else
		{
			int remain = 0;
			for (int i = arraySize - 1; i >= 0; --i)
			{
				long long tmp = (long long)bigDecimal.array[i] - remain - array[i];
				if (tmp < 0)
				{
					remain = 1;
					tmp += 1LL << 32;
				}
				else
				{
					remain = 0;
				}
				array[i] = tmp;
			}
			sign = !sign;
		}
	}
}

void BigDecimal::operator >>= (const int& delta)
{
	int bigDelta = delta >> 5;
	int smallDelta = delta & ((1 << 5) - 1);
	for (int i = arraySize - 1; i - bigDelta >= 0; --i)
	{
		array[i] = array[i - bigDelta];
	}
	for (int i = 0; i < bigDelta && i < arraySize; ++i)
	{
		array[i] = 0;
	}
	if (smallDelta)
	{
		int remain = 0;
		for (int i = bigDelta; i < arraySize; ++i)
		{
			int newRemain = array[i] & ((1 << smallDelta) - 1);
			array[i] >>= smallDelta;
			array[i] += remain << (32 - smallDelta);
			remain = newRemain;
		}
	}
}

std::ostream& operator << (std::ostream& out, const BigDecimal& bigDecimal)
{
	if (bigDecimal.sign)
	{
		out << "-";
	}
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