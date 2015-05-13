#ifndef __LAMP_H__
#define __LAMP_H__

#include <iostream>
#include "Component.h"

class Lamp : public Component
{
    public:
        Lamp();
        void on();
        void off();
    protected:
    private:
};

#endif // __LAMP_H__
