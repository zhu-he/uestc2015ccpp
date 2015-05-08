#include <iostream>
#include "BigDecimal.h"

using namespace std;

const int scale = 10000;

int main()
{
	BigDecimal Pi(0, 1, scale);
	for (int i = 0; ; ++i)
	{
		BigDecimal s0(32, 4 * i + 1, scale);
		BigDecimal s1(1, 4 * i + 3, scale);
		BigDecimal s2(256, 10 * i + 1, scale);
		BigDecimal s3(64, 10 * i + 3, scale);
		BigDecimal s4(4, 10 * i + 5, scale);
		BigDecimal s5(4, 10 * i + 7, scale);
		BigDecimal s6(1, 10 * i + 9, scale);
		BigDecimal sum = (-s0 - s1 + s2 - s3 - s4 - s5 + s6) >> (10 * i + 6);
		if (sum.compareAbsTo(BigDecimal(0, 1, scale)) == 0)
		{
			break;
		}
		if (i % 2 == 1)
		{
			Pi = Pi - sum;
		}
		else
		{
			Pi = Pi + sum;
		}
	}
	cout << Pi << endl;
	return 0;
}
