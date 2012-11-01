#ifndef PLAYER_H
#define PLAYER_H

#include "Point.h"
#include "MovableObject.h"
#include "allegro5\allegro5.h"
#include "Key.h"
#include "Box.h"
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
	///<summary>Wszystkie skrzynki, którymi porusza gracz</summary>
	std::vector<Box*> boxes;
	void LoadBitmaps(std::string bitmapName, Key key);
	void Anim();
	void MoveBoxes(Point playerDestination);
	///<summary>Zwraca s¹siaduj¹c¹ lokacjê na podstawie klawisza (lokacja 0,0 + Key::Right = lokacja 0,30)</summary>
	Point GetPointMoveDirection(Point point, Key key);
public:
	Player(Point &location, std::vector<Box*> boxes);
	void Update();
	void KeyPressed(Key key);
	void KeyReleased(Key key);
	~Player();
};

#endif