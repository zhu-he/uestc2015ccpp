#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

using namespace std;

class Employee
{
    public:
        Employee();
        Employee(string name);
        string getName();
        void setLevel(int level);
        int getLevel();
    protected:
        string _name;
        int _level;
};

#endif // EMPLOYEE_H
