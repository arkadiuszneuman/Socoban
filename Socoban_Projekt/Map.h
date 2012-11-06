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
	
	void CreateObjects(unsigned short map[22][20]);
public:
	Map();
	~Map();
	void Dispose();
	void DrawObjects();
	bool UpdateObjects();
	void KeyPressed(Key key);
	void KeyReleased(Key key);
	void LoadMap(std::string mapName);
};

#endif