#include <cstdio>
#include "IntStack.h"

int main()
{
	IntStack intStack;
	intStack.push(1);
	intStack.push(2);
	intStack.push(3);
	while (!intStack.empty())
	{
		int t = intStack.top();
		intStack.pop();
		printf("%d\n", t);
	}
	intStack.push(4);
	intStack.push(5);
	while (!intStack.empty())
	{
		int t = intStack.top();
		intStack.pop();
		printf("%d\n", t);
	}
	return 0;
}
