#include "Floor.h"

Floor::Floor(Point &location, bool endPoint)
	: BaseObject(location)
{
	bitmap = endPoint ? engine->GetBMP("menu//destination.bmp") : engine->GetBMP("menu//floor.bmp");
	this->endPoint = endPoint;
}

bool Floor::IsEndpoint()
{
	return this->endPoint;
}