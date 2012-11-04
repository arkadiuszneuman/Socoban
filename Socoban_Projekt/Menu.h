#ifndef MENU_H
#define MENU_H

#include "IButtonClickedEvent.h"
#include "Button.h"
#include <vector>

class Menu : IButtonClickedEvent, public IMouseEvents
{
private:
	void ButtonClicked(std::string name);
	std::vector<Button> buttons;
public:
	Menu();
	void Draw();

	void MouseMove(Mouse mouse);
	void MouseButtonDown(Mouse mouse);
	void MouseButtonUp(Mouse mouse);
};

#endif