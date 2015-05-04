#include "Sales.h"

Sales::Sales(string name)
{
    _name = name;
    _saleCount = 0;
}

void Sales::setSaleCount(int saleCount)
{
    _saleCount = saleCount;
}
