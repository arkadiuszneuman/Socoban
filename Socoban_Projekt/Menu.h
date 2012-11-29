#ifndef MENU_H
#define MENU_H

#include "IButtonClickedEvent.h"
#include "Button.h"
#include "HighscoreCollection.h"
#include "HighscoreDrawer.h"
#include <vector>
#include <time.h>
#include <ctime>
#include "GameWindow.h"

class Menu : IButtonClickedEvent
{
private:
	void CreateMainMenu();
	void CreateMapsMenu();
	void CreateHighscoreMenu();
	void CreateGameMenu(std::string levelName);
	void ButtonClicked(std::string name);
	void DrawGameText();
	void ClearButtons();

	Engine *engine;
	std::vector<Button*> buttons;
	Bitmap *bitmap, *menuBitmap, *highscoreBitmap, *gameBitmap;
	GameWindow *gameWindow;
	std::string actualMap, mapToLoad, playingTime;
	bool freeze, isInGame;
	time_t startTime;
	int playerSteps;
	HighscoreCollection *highscore;
	HighscoreDrawer *highscoreDrawer;
public:
	bool IsInEditor;

	Menu();
	~Menu();

	void Draw();
	void Update(int playerSteps);

	std::string GetMap();

	void NextMap();
	bool IsFreezed();
};

#endif