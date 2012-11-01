#include "Map.h"
#include "Player.h"
#include "Floor.h"
#include "Box.h"

Map::Map(std::string mapName)
{
	objects.push_back(new Floor(Point(0, 0)));
	objects.push_back(new Floor(Point(0, 30)));

	std::vector<Box*> boxes;
	boxes.push_back(new Box(Point(30, 60)));
	boxes.push_back(new Box(Point(30, 90)));
	boxes.push_back(new Box(Point(30, 120)));

	for (int i = 0; i < boxes.size(); ++i)
	{
		objects.push_back(boxes[i]);
		movableObjects.push_back(boxes[i]);
	}

	player = new Player(Point(30, 30), boxes);
	movableObjects.push_back(player);
	objects.push_back(player);
}

void Map::DrawObjects()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Draw();
	}
}

void Map::UpdateObjects()
{
	for (int i = 0; i < movableObjects.size(); ++i)
	{
		movableObjects[i]->Update();
	}
}

void Map::KeyPressed(Key key)
{
	player->KeyPressed(key);
}

void Map::KeyReleased(Key key)
{
	player->KeyReleased(key);
}

Map::~Map()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		delete(objects[i]);
	}

	objects.clear();
}