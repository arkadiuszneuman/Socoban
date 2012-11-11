#ifndef PLAYER_H
#define PLAYER_H

#include "Point.h"
#include "MovableObject.h"
#include "allegro5\allegro5.h"
#include "Key.h"
#include "Box.h"
#include "Wall.h"
#include "Floor.h"
#include <map>
#include <vector>

class Player : public MovableObject
{
private:
	Key pressedKey;
	///<summary>Kierunek, w którym zwrócony jest gracz</summary>
	Key moveDirection;
	int framesCount;
	std::map<const int, std::vector<Bitmap*> > animMove;
	std::vector<Bitmap*> animEnd;
	///<summary>Wszystkie skrzynki, którymi porusza gracz</summary>
	std::vector<Box*> boxes;
	std::vector<Wall*> walls;
	std::vector<Floor*> endPoints;

	void LoadBitmaps(std::string bitmapName, Key key);
	void LoadEndBitmaps();
	void Anim();
	void EndAnim();
	bool CheckBoxes(Point playerDestination);
	bool CheckWalls(Point destination);
	bool CheckEnd();
	bool animEnded;
	bool showEndAnim;
	bool isEnded;

	int steps;
	///<summary>Zwraca s¹siaduj¹c¹ lokacjê na podstawie klawisza (lokacja 0,0 + Key::Right = lokacja 0,30)</summary>
	Point GetPointMoveDirection(Point point, Key key);
public:
	Player(Point &location);
	void SetBoxes(std::vector<Box*> &boxes);
	void SetWalls(std::vector<Wall*> &walls);
	void SetEndpoints(std::vector<Floor*> &endPoints);
	void Update();
	void KeyPressed(Key key);
	void KeyReleased(Key key);
	bool IsEnded();
	int GetSteps();
	~Player();
};

#endif