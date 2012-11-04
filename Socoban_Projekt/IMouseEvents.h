#ifndef IMOUSEEVENTS_H
#define IMOUSEEVENTS_H

#include "Mouse.h"

class IMouseEvents
{
public:
	virtual void MouseMove(Mouse mouse) = 0;
	virtual void MouseButtonDown(Mouse mouse) = 0;
	virtual void MouseButtonUp(Mouse mouse) = 0;
};

#endif