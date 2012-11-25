#ifndef BUTTON_H
#define BUTTON_H

#include "BaseObject.h"
#include "IButtonClickedEvent.h"
#include <string>
#include <vector>

class Button : public BaseObject
{
private:
	Bitmap *bitmaps[3];
	IButtonClickedEvent *buttonClickedEvent;
	bool IsMouseOver(Mouse mouse);
	bool isMouseDown;
	bool threeState;
	std::string name;
public:
	Button(std::string name, Point &location, IButtonClickedEvent *buttonClickedEvent, bool threeState);
	void MouseMove(Mouse mouse);
	void MouseDown(Mouse mouse);
	void MouseUp(Mouse mouse);
	~Button();
};

#endif