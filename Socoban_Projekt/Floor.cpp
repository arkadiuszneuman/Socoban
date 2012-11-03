#include "Floor.h"

Floor::Floor(Point &location, bool endPoint)
	: BaseObject(location)
{
	bitmap = endPoint ? engine->GetBMP("destination.bmp") : engine->GetBMP("floor.bmp");
	this->endPoint = endPoint;
}