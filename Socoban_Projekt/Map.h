#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include "BaseObject.h"
#include "MovableObject.h"
#include "Player.h"

class Map
{
private:
	std::vector<BaseObject*> objects;
	std::vector<MovableObject*> movableObjects;

	Player *player;
public:
	Map(std::string mapName);
	~Map();
	void DrawObjects();
	void UpdateObjects();
	void KeyPressed(Key key);
	void KeyReleased(Key key);
};

#endif