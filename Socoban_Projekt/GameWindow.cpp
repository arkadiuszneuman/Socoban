#include "GameWindow.h"

GameWindow::GameWindow(IButtonClickedEvent *btnClickedEvent, std::string windowName,
					   std::string firstBtnName, std::string secondBtnName, bool showCaret)
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

	this->showCaret = showCaret;
	this->engine->AddKeyboardEvent(this);
}

void GameWindow::Draw()
{
	windowBitmap->Draw((engine->GetDisplayWidth() / 2) - (windowBitmap->GetWidth() / 2),
		(engine->GetDisplayHeight() / 2) - (windowBitmap->GetHeight() / 2));

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->Draw();
	}

	if (showCaret)
	{
		engine->DrawGameText(text, 320, 288, 50, 50, 50, false, true);
		engine->DrawLine(320 + (text.length() * 9), 290, 
			320 + (text.length() * 9), 305, 0, 0, 0, 2);
	}
}

void GameWindow::KeyDownEvent(Key key)
{

}

void GameWindow::KeyUpEvent(Key key)
{

}

void GameWindow::CharEntered(char c)
{
	if (showCaret)
	{
		if (text.length() < 17)
		{
			if (c >= 32 && c <= 126)
			{
				text += c;
			}
		}
		
		if (c == 8 && text.length() > 0) //backspace
		{
			text = text.substr(0, text.length() - 1);
		}
	}
}

std::string GameWindow::GetText()
{
	return this->text;
}

GameWindow::~GameWindow()
{
	this->engine->RemoveKeyboardEvent(this);

	for (int i = 0; i < buttons.size(); ++i)
	{
		delete buttons[i];
	}
}