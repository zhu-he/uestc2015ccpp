#include <iostream>
#include "SafeArray.h"

using namespace std;

int main()
{
	SafeArray<int> a(10, 123);
	a[0] = 1;
	a[2] = 2;
	a[8] = 10900;
	cout << a;
	SafeArray<int> b(5);
	b[0] = 1;
	b[2] = 2;
	cout << b;
	return 0;
}
