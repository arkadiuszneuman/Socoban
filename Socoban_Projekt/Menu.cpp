#include "Menu.h"
#include <sstream>

Menu::Menu()
{
	bitmap = NULL;
	windowBitmap = NULL;
	actualMap = "";
	freeze = false;
	isInGame = false;

	menuBitmap = Engine::GetInstance()->GetBMP("menu/menubitmap.bmp");
	highscoreBitmap = Engine::GetInstance()->GetBMP("menu/highscorebitmap.bmp");
	gameBitmap = Engine::GetInstance()->GetBMP("menu/game1.bmp");

	CreateMainMenu();
}

void Menu::CreateMainMenu()
{
	buttons.clear();

	buttons.push_back(Button("newgame", Point(276, 250), this));
	buttons.push_back(Button("choosenmap", Point(276, 290), this));
	buttons.push_back(Button("highscore", Point(276, 330), this));
	buttons.push_back(Button("editor", Point(276, 370), this));
	buttons.push_back(Button("end", Point(276, 450), this));

	bitmap = menuBitmap;
	windowBitmap = NULL;
	mapToLoad = "menu";

	isInGame = false;
}

void Menu::CreateMapsMenu()
{
	buttons.clear();

	buttons.push_back(Button("map/mapno1", Point(130, 200), this));
	buttons.push_back(Button("map/mapno2", Point(130, 250), this));
	buttons.push_back(Button("map/mapno3", Point(130, 300), this));
	buttons.push_back(Button("map/mapno4", Point(130, 350), this));
	buttons.push_back(Button("map/mapno5", Point(130, 400), this));
	buttons.push_back(Button("map/mapno6", Point(430, 200), this));
	buttons.push_back(Button("map/mapno7", Point(430, 250), this));
	buttons.push_back(Button("map/mapno8", Point(430, 300), this));
	buttons.push_back(Button("map/mapno9", Point(430, 350), this));
	buttons.push_back(Button("map/mapno10", Point(430, 400), this));

	buttons.push_back(Button("back", Point(500, 520), this));
	buttons.push_back(Button("usermap", Point(280, 450), this));

	bitmap = menuBitmap;
	windowBitmap = NULL;
}

void Menu::CreateGameMenu(std::string levelName)
{
	buttons.clear();

	buttons.push_back(Button("restart", Point(Engine::GetInstance()->GetDisplayWidth() - 120, 30), this));
	buttons.push_back(Button("close", Point(Engine::GetInstance()->GetDisplayWidth() - 120, 70), this));

	actualMap = levelName;
	mapToLoad = levelName;
	bitmap = gameBitmap;
	windowBitmap = NULL;

	isInGame = true;
	startTime = time(NULL);
}

void Menu::CreateGameWindow(std::string windowName, std::string firstBtnName, std::string secondBtnName)
{
	this->windowBitmap = Engine::GetInstance()->GetBMP("menu/windows/" + windowName + ".bmp");

	Point bitmapLocation((Engine::GetInstance()->GetDisplayWidth() / 2) - (windowBitmap->GetWidth() / 2),
			(Engine::GetInstance()->GetDisplayHeight() / 2) - (windowBitmap->GetHeight() / 2));

	buttons.push_back(Button("windows/" + firstBtnName, Point(bitmapLocation.GetX() + 20, 
		bitmapLocation.GetY() + this->windowBitmap->GetHeight() - 30), this));
	buttons.push_back(Button("windows/" + secondBtnName, Point(bitmapLocation.GetX() + this->windowBitmap->GetWidth() - 80, 
		bitmapLocation.GetY() + this->windowBitmap->GetHeight() - 30), this));
}

void Menu::ButtonClicked(std::string name)
{
	if (name == "choosenmap")
	{
		CreateMapsMenu();
	}
	else if (name == "back")
	{
		CreateMainMenu();
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
		CreateMainMenu();	
	}
	else if (name == "windows/next")
	{
		std::string lvl = "lvl";
		int lvlNo = atoi(actualMap.substr(actualMap.size() - 1, actualMap.size()).c_str());
		std::stringstream out;
		out << lvlNo + 1;
		lvl += out.str();

		freeze = false;
		CreateGameMenu(lvl);	
	}
	else if (name == "end")
	{
		Engine::GetInstance()->endGameLoop = true;
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
		CreateGameWindow("congratulations", "next", "endsmall");
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
		Engine::GetInstance()->DrawBitmap(bitmap, Engine::GetInstance()->GetDisplayWidth() - bitmap->GetWidth(), 
			Engine::GetInstance()->GetDisplayHeight() - bitmap->GetHeight());
	}

	if (windowBitmap != NULL)
	{
		windowBitmap->Draw((Engine::GetInstance()->GetDisplayWidth() / 2) - (windowBitmap->GetWidth() / 2),
			(Engine::GetInstance()->GetDisplayHeight() / 2) - (windowBitmap->GetHeight() / 2));
	}
	
	if (isInGame)
	{
		Engine::GetInstance()->DrawGameText(playingTime, Engine::GetInstance()->GetDisplayWidth() - 110, 500, 255, 255, 255);
	}

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].Draw();
	}
}

void Menu::Update()
{
	if (isInGame)
	{
		time_t endTime = time(NULL);
		time_t diff = endTime - startTime;
		
		char buffer[80];
		strftime (buffer, 80,"%X", gmtime(&diff));
		playingTime = buffer;
	}
}

void Menu::MouseMove(Mouse mouse)
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].MouseMove(mouse);
	}
}

void Menu::MouseButtonDown(Mouse mouse)
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].MouseDown(mouse);
	}
}

void Menu::MouseButtonUp(Mouse mouse)
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].MouseUp(mouse);
	}
}