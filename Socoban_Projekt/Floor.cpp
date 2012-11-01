#include "Floor.h"

Floor::Floor(Point &location)
	: BaseObject(location)
{
	bitmap = engine->LoadBMP("floor.bmp");
}