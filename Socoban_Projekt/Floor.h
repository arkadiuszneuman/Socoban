#ifndef FLOOR_H
#define FLOOR_H

#include "Point.h"
#include "BaseObject.h"

class Floor : public BaseObject
{
private:
	bool endPoint;
public:
	Floor(Point &location, bool endPoint);
};

#endif