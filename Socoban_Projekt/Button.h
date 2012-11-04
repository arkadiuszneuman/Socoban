#ifndef BUTTON_H
#define BUTTON_H

#include "BaseObject.h"
#include "IButtonClickedEvent.h"
#include <string>
#include <vector>

class Button : public BaseObject
{
private:
	ALLEGRO_BITMAP* bitmaps[3];
	IButtonClickedEvent *buttonClickedEvent;
	bool IsMouseOver(Mouse mouse);
	bool isMouseDown;
	std::string name;
public:
	Button(std::string name, Point &location, IButtonClickedEvent *buttonClickedEvent);
	void MouseMove(Mouse mouse);
	void MouseDown(Mouse mouse);
	void MouseUp(Mouse mouse);
	~Button();
};

#endif