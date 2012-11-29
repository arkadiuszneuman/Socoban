#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <string>
#include "Bitmap.h"
#include "Engine.h"
#include "Point.h"
#include "Button.h"
#include "IButtonClickedEvent.h"

class GameWindow : public IKeyboardEvents
{
private:
	Bitmap *windowBitmap;
	Engine *engine;
	bool showCaret;
	std::string text;
	std::vector<Button *> buttons;
public:
	GameWindow(IButtonClickedEvent *btnClickedEvent, std::string windowName, std::string firstBtnName, std::string secondBtnName, bool showCaret);
	void GameWindow::KeyDownEvent(Key key);
	void GameWindow::KeyUpEvent(Key key);
	void GameWindow::CharEntered(char c);

	std::string GetText();
	~GameWindow();

	void Draw();
};

#endif