#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Circuit.h"

class Circuit;

class Button
{
    public:
        Button();
        void on();
        void off();
        void setCircuit(Circuit* circuit);
    private:
        Circuit* circuit;
};

#endif // __BUTTON_H__
