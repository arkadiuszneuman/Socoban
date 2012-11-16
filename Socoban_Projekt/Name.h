#ifndef NAME_H
#define NAME_H

#include "Point.h"
#include "BaseObject.h"

class Name : public BaseObject
{
public:
	Name(Point &location);
	void Draw();
};

#endif