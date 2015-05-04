#include "Employee.h"

Employee::Employee()
{

}

Employee::Employee(string name)
{
    _name = name;
}

string Employee::getName()
{
    return _name;
}

void Employee::setLevel(int level)
{
    _level = level;
}

int Employee::getLevel()
{
    return _level;
}
