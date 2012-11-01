#include "BaseObject.h"

BaseObject::BaseObject(Point &p)
{
	this->location = p;
	this->engine = Engine::GetInstance();
}

void BaseObject::DrawBitmap(ALLEGRO_BITMAP *bitmap)
{
	engine->DrawBitmap(bitmap, location.GetX(), location.GetY());
}