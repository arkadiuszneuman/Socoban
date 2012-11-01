#ifndef GAME_H
#define GAME_H

#include "allegro5\allegro.h"
#include "IGame.h"

class Game : public IGame
{
public:
	void Start();
	void Draw();
	void Update();
	void KeyDownEvent(Key key);
	void KeyUpEvent(Key key);
};

#endif