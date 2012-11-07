#ifndef MENU_H
#define MENU_H

#include "IButtonClickedEvent.h"
#include "Button.h"
#include <vector>

class Menu : IButtonClickedEvent, public IMouseEvents
{
private:
	void CreateMainMenu();
	void CreateMapsMenu();
	void CreateGameMenu(std::string levelName);
	void ButtonClicked(std::string name);

	std::vector<Button> buttons;
	Bitmap *bitmap, *menuBitmap, *highscoreBitmap, *gameBitmap;
	std::string actualMap;
public:
	Menu();
	void Draw();
	std::string GetMap();

	void MouseMove(Mouse mouse);
	void MouseButtonDown(Mouse mouse);
	void MouseButtonUp(Mouse mouse);
};

#endif