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
	///<summary>Kierunek, w którym zwrócony jest gracz</summary>
	Key moveDirection;
	int framesCount;
	std::map<const int, std::vector<ALLEGRO_BITMAP*> > animMove;
	void LoadBitmaps(std::string bitmapName, Key key);
public:
	Player(Point &location);
	void Update();
	void KeyPressed(Key key);
	void KeyReleased(Key key);
	//void Anim
	~Player();
};

#endif