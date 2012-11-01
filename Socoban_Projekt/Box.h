#ifndef BOX_H
#define BOX_H

#include "Point.h"
#include "MovableObject.h"

class Box : public MovableObject
{
public:
	Box(Point &location);
};

#endif