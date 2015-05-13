#include "Circuit.h"

Circuit::Circuit()
{

}

void Circuit::setSwitch(Button* button)
{
    button->setCircuit(this);
}

void Circuit::append(Component* component)
{
    components.push_back(component);
}

void Circuit::on()
{
    for (auto *component : components)
    {
        component->on();
    }
}

void Circuit::off()
{
    for (auto *component : components)
    {
        component->off();
    }
}
