#include "GameWindow.h"

GameWindow::GameWindow(IButtonClickedEvent *btnClickedEvent, std::string windowName, std::string firstBtnName, std::string secondBtnName)
{
	this->engine = Engine::GetInstance();
	this->windowBitmap = engine->GetBMP("menu/windows/" + windowName + ".bmp");

	Point bitmapLocation((engine->GetDisplayWidth() / 2) - (windowBitmap->GetWidth() / 2),
			(engine->GetDisplayHeight() / 2) - (windowBitmap->GetHeight() / 2));

	if (firstBtnName.length() > 0)
	{
		buttons.push_back(Button("windows/" + firstBtnName, Point(bitmapLocation.GetX() + 20, 
			bitmapLocation.GetY() + this->windowBitmap->GetHeight() - 30), btnClickedEvent, true));
	}
	if (secondBtnName.length() > 0)
	{
		buttons.push_back(Button("windows/" + secondBtnName, Point(bitmapLocation.GetX() + this->windowBitmap->GetWidth() - 80, 
			bitmapLocation.GetY() + this->windowBitmap->GetHeight() - 30), btnClickedEvent, true));
	}
}