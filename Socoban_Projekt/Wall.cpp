#include "Wall.h"

Wall::Wall(Point &location)
	: BaseObject(location)
{
	bitmap = engine->GetBMP("menu//wall.bmp");
}