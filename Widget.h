#ifndef WIDGET_H
#define WIDGET_H

#include "Emulator.h"

class Widget
{
public:
    Widget(Emulator rhs);
private:
    Emulator emulator_;
};

#endif // WIDGET_H
