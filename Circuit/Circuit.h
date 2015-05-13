#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

#include <vector>
#include "Button.h"
#include "Component.h"

using namespace std;

class Button;

class Circuit
{
    public:
        Circuit();
        void setSwitch(Button* button);
        void append(Component* component);
        void on();
        void off();
    private:
        vector<Component*> components;
};

#endif // __CIRCUIT_H__
