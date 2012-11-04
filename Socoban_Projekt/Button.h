#ifndef BUTTON_H
#define BUTTON_H

#include "BaseObject.h"
#include <string>
#include <vector>

class Button : BaseObject
{
private:
	ALLEGRO_BITMAP* bitmaps[3];
public:
	Button(std::string name, Point &location);
};

#endif