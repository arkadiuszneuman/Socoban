#ifndef IGAME_H
#define IGAME_H

#include "Key.h"
#include "Mouse.h"

class IGame
{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void KeyDownEvent(Key key) = 0;
	virtual void KeyUpEvent(Key key) = 0;
};

#endif