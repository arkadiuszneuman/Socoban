#ifndef EDITOR_H
#define EDITOR_H

#include "IButtonClickedEvent.h"
#include "Button.h"
#include "HighscoreCollection.h"
#include "HighscoreDrawer.h"
#include <vector>
#include <map>
#include "ObjectType.h"

class Editor : IButtonClickedEvent, public IMouseEvents
{
private:
	void ButtonClicked(std::string name);
	void ChangeBrush(ObjectType objectType);

	Engine *engine;
	std::map<ObjectType, Button*> buttonsDictionary;
	std::vector<Button> buttons;
	Bitmap *bitmap;
	bool isEnded;
	ObjectType brush;
	Point selectedBrushLocation;
	int r, g, b;
public:
	Editor();
	~Editor();

	bool IsEnded();

	void Draw();

	void MouseMove(Mouse mouse);
	void MouseButtonDown(Mouse mouse);
	void MouseButtonUp(Mouse mouse);

	void CharEntered(char c);
};

#endif