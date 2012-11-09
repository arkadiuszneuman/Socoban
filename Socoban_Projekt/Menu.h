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
	void CreateGameWindow(std::string windowName, std::string firstBtnName, std::string secondBtnName);
	void ButtonClicked(std::string name);

	std::vector<Button> buttons;
	Bitmap *bitmap, *menuBitmap, *highscoreBitmap, *gameBitmap, *windowBitmap;
	std::string actualMap, mapToLoad;
	bool freeze;
public:
	Menu();
	void Draw();
	std::string GetMap();

	void MouseMove(Mouse mouse);
	void MouseButtonDown(Mouse mouse);
	void MouseButtonUp(Mouse mouse);

	void NextMap();
	bool IsFreezed();
};

#endif