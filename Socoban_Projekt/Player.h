#ifndef PLAYER_H
#define PLAYER_H

#include "Point.h"
#include "MovableObject.h"
#include "allegro5\allegro5.h"
#include "Key.h"
#include <map>
#include <vector>

class Player : public MovableObject
{
private:
	Key pressedKey;
	int framesCount;
	std::map<const int, std::vector<ALLEGRO_BITMAP*> > animMove;
public:
	Player(Point &location);
	void Update();
	void KeyPressed(Key key);
	void KeyReleased(Key key);
	~Player();
};

#endif