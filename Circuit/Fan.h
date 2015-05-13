#ifndef __FAN_H__
#define __FAN_H__

#include <iostream>
#include "Component.h"

class Fan : public Component
{
    public:
        Fan();
        void on();
        void off();
    protected:
    private:
};

#endif // __FAN_H__
