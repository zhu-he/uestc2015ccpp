#include <iostream>
#include "Sales.h"

using namespace std;

int main()
{
    Sales yueShen("God Yue");
    yueShen.setSaleCount(100);
    yueShen.setLevel(99);
    cout << yueShen.getName() << " " << yueShen.getLevel() << endl;
    return 0;
}
