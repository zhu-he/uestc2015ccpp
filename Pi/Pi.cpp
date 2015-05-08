#include <iostream>
#include <omp.h>
#include <ctime>
#include <cmath>
#include "BigDecimal.h"

using namespace std;

const int scale = 100000;

int main()
{
	time_t startTime = clock();
	int coreNum = omp_get_num_procs();
	BigDecimal* Pi[coreNum];
	for (int i = 0; i < coreNum; ++i)
	{
		Pi[i] = new BigDecimal(0, 1, scale);
	}
	#pragma omp parallel for
	for (int i = 0; i < scale / 3 + 3; ++i)
	{
		BigDecimal sum(256, 10 * i + 1, scale);
		sum += BigDecimal(1, 10 * i + 9, scale);
		sum -= BigDecimal(1, 4 * i + 3, scale);
		sum -= BigDecimal(64, 10 * i + 3, scale);
		sum -= BigDecimal(4, 10 * i + 5, scale);
		sum -= BigDecimal(4, 10 * i + 7, scale);
		sum -= BigDecimal(32, 4 * i + 1, scale);
		sum >>= 10 * i + 6;
		if (i % 2 == 1)
		{
			*Pi[omp_get_thread_num()] -= sum;
		}
		else
		{
			*Pi[omp_get_thread_num()] += sum;
		}
	}
	cout << "Time: " << (double)(clock() - startTime) / CLOCKS_PER_SEC << "s" << endl;
	for (int i = 1; i < coreNum; ++i)
	{
		*Pi[0] += *Pi[i];
	}
	cout << *Pi[0] << endl;
	return 0;
}
