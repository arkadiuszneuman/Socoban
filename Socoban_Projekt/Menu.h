#ifndef MENU_H
#define MENU_H

#include "IButtonClickedEvent.h"
#include "Button.h"
#include "HighscoreCollection.h"
#include "HighscoreDrawer.h"
#include <vector>
#include <time.h>
#include <ctime>

class Menu : IButtonClickedEvent, public IMouseEvents
{
private:
	void CreateMainMenu();
	void CreateMapsMenu();
	void CreateHighscoreMenu();
	void CreateGameMenu(std::string levelName);
	void CreateGameWindow(std::string windowName, std::string firstBtnName, std::string secondBtnName);
	void ButtonClicked(std::string name);
	void DrawGameText();

	Engine *engine;
	std::vector<Button> buttons;
	Bitmap *bitmap, *menuBitmap, *highscoreBitmap, *gameBitmap, *windowBitmap;
	std::string actualMap, mapToLoad, playingTime, playerName;
	bool freeze, isInGame;
	time_t startTime;
	int playerSteps;
	bool showCaret;
	HighscoreCollection *highscore;
	HighscoreDrawer *highscoreDrawer;
public:
	bool IsInEditor;

	Menu();
	~Menu();

	void Draw();
	void Update(int playerSteps);

	std::string GetMap();

	void MouseMove(Mouse mouse);
	void MouseButtonDown(Mouse mouse);
	void MouseButtonUp(Mouse mouse);

	void NextMap();
	bool IsFreezed();

	void CharEntered(char c);
};

#endif