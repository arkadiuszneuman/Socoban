#ifndef EDITOR_H
#define EDITOR_H

#include "IButtonClickedEvent.h"
#include "Button.h"
#include "HighscoreCollection.h"
#include "HighscoreDrawer.h"
#include <vector>
#include <map>
#include "ObjectType.h"
#include "BaseObject.h"
#include "Player.h"
#include "GameWindow.h"
#include "Map.h"

class Editor : IButtonClickedEvent, public IMouseEvents
{
private:
	void ButtonClicked(std::string name);
	void ChangeBrush(ObjectType objectType);
	Point ConvertLogicalToPoint(int x, int y);
	void AddObject(int x, int y, ObjectType objectType);
	void RemoveObject(int x, int y);
	bool SaveMap(std::string name);
	bool IsFileExists(const char *filename);

	Engine *engine;
	GameWindow *gameWindow;
	std::map<ObjectType, Button*> buttonsDictionary;
	std::vector<Button *> buttons;
	std::vector<Floor*> floors;
	std::vector<Floor*> destinations;
	std::vector<Box*> boxes;
	std::vector<Wall*> walls;
	Player *player;
	Bitmap *bitmap;
	Map *map;
	bool isEnded;
	ObjectType brush;
	Point selectedBrushLocation;
	int r, g, b;
public:
	Editor(Map *map);
	~Editor();

	bool IsEnded();

	void Draw();

	void MouseMove(Mouse mouse);
	void MouseButtonDown(Mouse mouse);
	void MouseButtonUp(Mouse mouse);

	void CharEntered(char c);
};

#endif