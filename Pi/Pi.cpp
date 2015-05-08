#include <iostream>
// #include <ctime>
#include "BigDecimal.h"

using namespace std;

const int scale = 10000;

int main()
{
	// time_t startTime = clock();
	BigDecimal Pi(0, 1, scale);
	for (int i = 0; ; ++i)
	{
		BigDecimal sum(32, 4 * i + 1, scale);
		sum += BigDecimal(1, 4 * i + 3, scale);
		sum += BigDecimal(64, 10 * i + 3, scale);
		sum += BigDecimal(4, 10 * i + 5, scale);
		sum += BigDecimal(4, 10 * i + 7, scale);
		sum -= BigDecimal(256, 10 * i + 1, scale);
		sum -= BigDecimal(1, 10 * i + 9, scale);
		sum >>= 10 * i + 6;
		if (sum.isZero())
		{
			break;
		}
		if (i % 2 == 1)
		{
			Pi += sum;
		}
		else
		{
			Pi -= sum;
		}
	}
	// cout << "Time: " << (double)(clock() - startTime) / CLOCKS_PER_SEC << "s" << endl;
	cout << Pi << endl;
	return 0;
}
