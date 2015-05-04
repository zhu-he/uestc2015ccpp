#ifndef SALES_H
#define SALES_H

#include <string>
#include "Employee.h"

using namespace std;

class Sales : public Employee
{
    public:
        Sales(string name);
        void setSaleCount(int saleCount);
    protected:
        int _saleCount;
};

#endif // SALES_H
