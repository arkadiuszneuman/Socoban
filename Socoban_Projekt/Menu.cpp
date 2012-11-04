#include "Menu.h"

Menu::Menu()
{
	buttons.push_back(Button("end", Point(0, 0), this));
}

void Menu::ButtonClicked(std::string name)
{
	if (name == "end")
	{
		int i = 123;
	}
}

void Menu::Draw()
{
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