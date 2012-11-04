#ifndef GAME_H
#define GAME_H

#include "allegro5\allegro.h"
#include "IGame.h"
#include "Map.h"

class Game : public IGame
{
private:
	Map *map;
public:
	void Start();
	void Draw();
	void Update();
	void KeyDownEvent(Key key);
	void KeyUpEvent(Key key);
	void MouseMove(Mouse mouse);
	void MouseButtonDown(Mouse mouse);
	void MouseButtonUp(Mouse mouse);
};

#endif