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
	for (int i = 0; i < arraySize; ++i)
	{
		array[i] = remain / divisor;
		remain = remain - array[i] * divisor;
		remain <<= 32;
	}
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

BigDecimal operator - (BigDecimal bigDecimal)
{
	bigDecimal.sign = !bigDecimal.sign;
	return bigDecimal;
}

BigDecimal operator + (BigDecimal bigDecimal1, const BigDecimal& bigDecimal2)
{
	if (bigDecimal1.sign ^ bigDecimal2.sign)
	{
		return bigDecimal2 - (-bigDecimal1);
	}
	else
	{
		int remain = 0;
		for (int i = bigDecimal1.arraySize - 1; i >= 0; --i)
		{
			long long tmp = (long long)bigDecimal1.array[i] + bigDecimal2.array[i] + remain;
			bigDecimal1.array[i] = tmp & ((1LL << 32) - 1);
			remain = tmp >> 32;
		}
		return bigDecimal1;
	}
}

BigDecimal operator - (BigDecimal bigDecimal1, const BigDecimal& bigDecimal2)
{
	if (bigDecimal1.sign ^ bigDecimal2.sign)
	{
		return bigDecimal1 + (-bigDecimal2);
	}
	else
	{
		if (bigDecimal1.compareAbsTo(bigDecimal2) >= 0)
		{
			int remain = 0;
			for (int i = bigDecimal1.arraySize - 1; i >= 0; --i)
			{
				long long tmp = (long long)bigDecimal1.array[i] - remain - bigDecimal2.array[i];
				if (tmp < 0)
				{
					remain = 1;
					tmp += 1LL << 32;
				}
				else
				{
					remain = 0;
				}
				bigDecimal1.array[i] = tmp;
			}
		}
		else
		{
			int remain = 0;
			for (int i = bigDecimal1.arraySize - 1; i >= 0; --i)
			{
				long long tmp = (long long)bigDecimal2.array[i] - remain - bigDecimal1.array[i];
				if (tmp < 0)
				{
					remain = 1;
					tmp += 1LL << 32;
				}
				else
				{
					remain = 0;
				}
				bigDecimal1.array[i] = tmp;
			}
			bigDecimal1.sign = !bigDecimal1.sign;
		}
		return bigDecimal1;
	}
}

BigDecimal operator >> (BigDecimal bigDecimal, const int& delta)
{
	int bigDelta = delta >> 5;
	int smallDelta = delta & ((1 << 5) - 1);
	for (int i = bigDecimal.arraySize - 1; i - bigDelta >= 0; --i)
	{
		bigDecimal.array[i] = bigDecimal.array[i - bigDelta];
	}
	for (int i = 0; i < bigDelta; ++i)
	{
		bigDecimal.array[i] = 0;
	}
	if (smallDelta)
	{
		int remain = 0;
		for (int i = bigDelta; i < bigDecimal.arraySize; ++i)
		{
			int newRemain = bigDecimal.array[i] & ((1 << smallDelta) - 1);
			bigDecimal.array[i] >>= smallDelta;
			bigDecimal.array[i] += remain << (32 - smallDelta);
			remain = newRemain;
		}
	}
	return bigDecimal;
}

std::ostream& operator << (std::ostream& out, BigDecimal bigDecimal)
{
	if (bigDecimal.sign)
	{
		out << "-";
	}
	out << bigDecimal.array[0] << ".";
	for (int i = 0; i < bigDecimal.scale; ++i)
	{
		int remain = 0;
		for (int j = bigDecimal.arraySize - 1; j >= 1; --j)
		{
			long long tmp = bigDecimal.array[j] * 10LL + remain;
			bigDecimal.array[j] = tmp & ((1LL << 32) - 1);
			remain = tmp >> 32;
		}
		out << remain;
	}
	return out;
}