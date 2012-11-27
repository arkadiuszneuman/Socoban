#include "GameWindow.h"

GameWindow::GameWindow(IButtonClickedEvent *btnClickedEvent, std::string windowName, std::string firstBtnName, std::string secondBtnName)
{
	this->engine = Engine::GetInstance();
	this->windowBitmap = engine->GetBMP("menu/windows/" + windowName + ".bmp");

	Point bitmapLocation((engine->GetDisplayWidth() / 2) - (windowBitmap->GetWidth() / 2),
			(engine->GetDisplayHeight() / 2) - (windowBitmap->GetHeight() / 2));

	if (firstBtnName.length() > 0)
	{
		buttons.push_back(new Button("windows/" + firstBtnName, Point(bitmapLocation.GetX() + 20, 
			bitmapLocation.GetY() + this->windowBitmap->GetHeight() - 30), btnClickedEvent, true));
	}
	if (secondBtnName.length() > 0)
	{
		buttons.push_back(new Button("windows/" + secondBtnName, Point(bitmapLocation.GetX() + this->windowBitmap->GetWidth() - 80, 
			bitmapLocation.GetY() + this->windowBitmap->GetHeight() - 30), btnClickedEvent, true));
	}
}

void GameWindow::Draw()
{
	windowBitmap->Draw((engine->GetDisplayWidth() / 2) - (windowBitmap->GetWidth() / 2),
		(engine->GetDisplayHeight() / 2) - (windowBitmap->GetHeight() / 2));

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->Draw();
	}
}

GameWindow::~GameWindow()
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		delete buttons[i];
	}
}