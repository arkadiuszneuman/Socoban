#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "Point.h"
#include "Engine.h"

class BaseObject
{
private:
	
protected:
	Engine *engine;
	///<summary>Rozmiar tekstury (jednego kwadratu)</summary>
	
	ALLEGRO_BITMAP *bitmap;
	Point location;
public:
	static const int TextureSize = 30;

	BaseObject(Point &p);
	Point GetLocation();
	virtual void Draw();
};

#endif