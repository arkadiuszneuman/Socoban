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
	static const int texSize = 30;
	ALLEGRO_BITMAP *bitmap;
	Point location;
public:
	BaseObject(Point &p);
	virtual void Draw();
};

#endif