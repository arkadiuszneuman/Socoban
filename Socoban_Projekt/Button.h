#ifndef BUTTON_H
#define BUTTON_H

#include "BaseObject.h"
#include <string>
#include <vector>

class Button : public BaseObject
{
private:
	ALLEGRO_BITMAP* bitmaps[3];
	bool IsMouseOver(Mouse mouse);
public:
	Button(std::string name, Point &location);
	void MouseMove(Mouse mouse);
	void MouseDown(Mouse mouse);
	void MouseUp(Mouse mouse);
	~Button();
};

#endif