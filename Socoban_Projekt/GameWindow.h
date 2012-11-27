#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <string>
#include "Bitmap.h"
#include "Engine.h"
#include "Point.h"
#include "Button.h"
#include "IButtonClickedEvent.h"

class GameWindow
{
private:
	Bitmap *windowBitmap;
	Engine *engine;
	std::vector<Button> buttons;
public:
	GameWindow(IButtonClickedEvent *btnClickedEvent, std::string windowName, std::string firstBtnName, std::string secondBtnName);
};

#endif