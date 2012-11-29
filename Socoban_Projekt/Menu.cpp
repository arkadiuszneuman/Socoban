#include "Menu.h"
#include "Convert.h"

Menu::Menu()
{
	engine = Engine::GetInstance();
	bitmap = NULL;
	actualMap = "";
	freeze = false;
	isInGame = false;
	playerSteps = 0;
	this->IsInEditor = false;

	menuBitmap = engine->GetBMP("menu/menubitmap.bmp");
	highscoreBitmap = engine->GetBMP("menu/highscorebitmap.bmp");
	gameBitmap = engine->GetBMP("menu/game1.bmp");

	highscore = new HighscoreCollection();
	highscoreDrawer = NULL;

	gameWindow = NULL;

	CreateMainMenu();
}

void Menu::CreateMainMenu()
{
	ClearButtons();

	buttons.push_back(new Button("newgame", Point(276, 250), this, true));
	buttons.push_back(new Button("choosenmap", Point(276, 290), this, true));
	buttons.push_back(new Button("highscore", Point(276, 330), this, true));
	buttons.push_back(new Button("editor", Point(276, 370), this, true));
	buttons.push_back(new Button("end", Point(276, 450), this, true));

	bitmap = menuBitmap;
	mapToLoad = "menu";

	isInGame = false;
}

void Menu::CreateHighscoreMenu()
{
	ClearButtons();

	buttons.push_back(new Button("nexthigh", Point(345, 110), this, true));
	buttons.push_back(new Button("prevhigh", Point(10, 110), this, true));

	buttons.push_back(new Button("back", Point(500, 520), this, true));

	highscoreDrawer = new HighscoreDrawer(Point(10, 150), 255, 255, 255, 2);

	bitmap = highscoreBitmap;
}

void Menu::CreateMapsMenu()
{
	ClearButtons();

	buttons.push_back(new Button("map/mapno1", Point(130, 200), this, true));
	buttons.push_back(new Button("map/mapno2", Point(130, 250), this, true));
	buttons.push_back(new Button("map/mapno3", Point(130, 300), this, true));
	buttons.push_back(new Button("map/mapno4", Point(130, 350), this, true));
	buttons.push_back(new Button("map/mapno5", Point(130, 400), this, true));
	buttons.push_back(new Button("map/mapno6", Point(430, 200), this, true));
	buttons.push_back(new Button("map/mapno7", Point(430, 250), this, true));
	buttons.push_back(new Button("map/mapno8", Point(430, 300), this, true));
	buttons.push_back(new Button("map/mapno9", Point(430, 350), this, true));
	buttons.push_back(new Button("map/mapno10", Point(430, 400), this, true));

	buttons.push_back(new Button("back", Point(500, 520), this, true));
	buttons.push_back(new Button("usermap", Point(280, 450), this, true));

	bitmap = menuBitmap;
}

void Menu::CreateGameMenu(std::string levelName)
{
	ClearButtons();

	buttons.push_back(new Button("restart", Point(engine->GetDisplayWidth() - 120, 30), this, true));
	buttons.push_back(new Button("close", Point(engine->GetDisplayWidth() - 120, 70), this, true));

	actualMap = levelName;
	mapToLoad = levelName;
	bitmap = gameBitmap;

	isInGame = true;
	playerSteps = 0;
	startTime = time(NULL);
}

void Menu::ClearButtons()
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		delete buttons[i];
	}

	buttons.clear();
}

void Menu::ButtonClicked(std::string name)
{
	if (highscoreDrawer != NULL
		&& name != "nexthigh" && name != "prevhigh")
	{
		delete highscoreDrawer;
		highscoreDrawer = NULL;
	}

	if (name == "choosenmap")
	{
		CreateMapsMenu();
	}
	else if (name == "back")
	{
		CreateMainMenu();
	}
	else if (name == "highscore")
	{
		CreateHighscoreMenu();
	}
	else if (name == "nexthigh")
	{
		if (highscoreDrawer != NULL)
			highscoreDrawer->NextHighscore();
	}
	else if (name == "prevhigh")
	{
		if (highscoreDrawer != NULL)
			highscoreDrawer->PrevHighscore();
	}
	else if (name.substr(0, 9) == "map/mapno")
	{
		CreateGameMenu("lvl" + name.substr(9, 10));
	}
	else if (name == "newgame")
	{
		CreateGameMenu("lvl1");
	}
	else if (name == "restart")
	{
		CreateGameMenu(actualMap);
	}
	else if (name == "close" || name == "windows/endsmall")
	{
		freeze = false;

		if (gameWindow != NULL)
		{
			delete gameWindow;
			gameWindow = NULL;
		}

		CreateMainMenu();	
	}
	else if (name == "windows/next")
	{
		int lvlNo = Convert::ToInt(actualMap.substr(actualMap.size() - 1, actualMap.size()).c_str());

		if (gameWindow != NULL)
		{
			highscore->AddHighscore(lvlNo, gameWindow->GetText(), playingTime, playerSteps);

			playingTime = "";
			playerSteps = 0;

			delete gameWindow;
			gameWindow = NULL;
		}

		freeze = false;
		CreateGameMenu("lvl" + Convert::ToString(lvlNo + 1));	
	}
	else if (name == "end")
	{
		engine->endGameLoop = true;
	}
	else if (name == "editor")
	{
		ClearButtons();
		this->IsInEditor = true;
	}
}

void Menu::NextMap()
{
	this->freeze = true;

	if (actualMap == "lvl10")
	{

	}
	else
	{
		if (this->gameWindow == NULL && highscore->IsQualified(Convert::ToInt(actualMap.substr(actualMap.size() - 1, actualMap.size()).c_str())
			, playerSteps, playingTime))
		{
			this->gameWindow = new GameWindow(this, "highscore", "next", "", true);
		}
		else
		{
			this->gameWindow = new GameWindow(this, "congratulations", "next", "endsmall", true);
		}
	}
}

std::string Menu::GetMap()
{
	std::string map = mapToLoad;
	mapToLoad = "";
	return map;
}

bool Menu::IsFreezed()
{
	return this->freeze;
}

void Menu::Draw()
{
	if (bitmap != NULL)
	{
		engine->DrawBitmap(bitmap, engine->GetDisplayWidth() - bitmap->GetWidth(), 
			engine->GetDisplayHeight() - bitmap->GetHeight());
	}

	if (highscoreDrawer != NULL)
	{
		highscoreDrawer->Draw(highscore);
	}
	
	if (isInGame)
	{
		DrawGameText();
	}

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->Draw();
	}

	if (gameWindow != NULL)
	{
		gameWindow->Draw();
	}
}

void Menu::DrawGameText()
{
	int r = 255;
	int g = 160;
	int b = 0;

	engine->DrawGameText("Kroki:", engine->GetDisplayWidth() - (bitmap->GetWidth() / 2),
			engine->GetDisplayHeight() - 200, r, g, b, true, false);

	engine->DrawGameText(Convert::ToString(playerSteps), engine->GetDisplayWidth() - (bitmap->GetWidth() / 2),
		engine->GetDisplayHeight() - 175, r, g, b, true, false);

	engine->DrawGameText("Czas:", engine->GetDisplayWidth() - (bitmap->GetWidth() / 2),
		engine->GetDisplayHeight() - 125, r, g, b, true, false);

	engine->DrawGameText(playingTime, engine->GetDisplayWidth() - (bitmap->GetWidth() / 2),
		engine->GetDisplayHeight() - 100, r, g, b, true, false);
}

void Menu::Update(int playerSteps)
{
	if (isInGame && this->gameWindow == NULL)
	{
		time_t endTime = time(NULL);
		time_t diff = endTime - startTime;
		
		char buffer[80];
		strftime(buffer, 80,"%X", gmtime(&diff));
		playingTime = buffer;

		this->playerSteps = playerSteps;
	}

	if (buttons.size() == 0)
	{
		CreateMainMenu();
	}
}

Menu::~Menu()
{
	if (this->gameWindow != NULL)
	{
		delete this->gameWindow;
		this->gameWindow = NULL;
	}

	if (this->highscoreDrawer != NULL)
	{
		delete this->highscoreDrawer;
	}
}