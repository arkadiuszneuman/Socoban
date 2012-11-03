#ifndef WALL_H
#define WALL_H

#include "Point.h"
#include "BaseObject.h"

class Wall : public BaseObject
{
public:
	Wall(Point &location);
};

#endif