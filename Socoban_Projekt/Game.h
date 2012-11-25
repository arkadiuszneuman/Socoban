#ifndef GAME_H
#define GAME_H

#include "allegro5\allegro.h"
#include "IGame.h"
#include "Map.h"
#include "Menu.h"
#include "Editor.h"

class Game : public IKeyboardEvents, public IGame
{
private:
	Map *map;
	Menu *menu;
	Editor *editor;
public:
	void Start();
	void Draw();
	void Update();
	void KeyDownEvent(Key key);
	void KeyUpEvent(Key key);

	void CharEntered(char c);
};

#endif