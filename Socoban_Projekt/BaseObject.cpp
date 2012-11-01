#include "BaseObject.h"

BaseObject::BaseObject(Point &p)
{
	this->location = p;
	this->engine = Engine::GetInstance();
}

void BaseObject::Draw()
{
	engine->DrawBitmap(bitmap, location.GetX(), location.GetY());
}

Point BaseObject::GetLocation()
{
	return this->location;
}