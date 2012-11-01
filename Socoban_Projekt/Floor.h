#ifndef FLOOR_H
#define FLOOR_H

#include "Point.h"
#include "BaseObject.h"

class Floor : public BaseObject
{
public:
	Floor(Point &location);
};

#endif