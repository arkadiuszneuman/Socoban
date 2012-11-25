#include "Box.h"

Box::Box(Point &location)
	: MovableObject(location)
{
	bitmap = engine->GetBMP("menu//box.bmp");
}