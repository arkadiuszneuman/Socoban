#include "Menu.h"

Menu::Menu()
{
	bitmap = NULL;
	actualMap = "";

	menuBitmap = Engine::GetInstance()->GetBMP("menu/menubitmap.bmp");
	highscoreBitmap = Engine::GetInstance()->GetBMP("menu/highscorebitmap.bmp");

	CreateMapsMenu(); //za³adowanie bitmap
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
		actualMap = "lvl" + name.substr(9, 10);
		bitmap = NULL;
	}
	else if (name == "end")
	{
		Engine::GetInstance()->endGameLoop = true;
	}
}

std::string Menu::GetMap()
{
	std::string map = actualMap;
	actualMap = "";
	return map;
}

void Menu::Draw()
{
	if (bitmap != NULL)
	{
		Engine::GetInstance()->DrawBitmap(bitmap, 0, 0);
	}

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].Draw();
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