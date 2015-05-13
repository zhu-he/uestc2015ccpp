#include "Button.h"

Button::Button()
{

}

void Button::on()
{
    circuit->on();
}

void Button::off()
{
    circuit->off();
}

void Button::setCircuit(Circuit* circuit)
{
    this->circuit = circuit;
}
