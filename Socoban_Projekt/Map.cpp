#include "Map.h"
#include "Player.h"
#include "Wall.h"
#include "Floor.h"
#include "Box.h"

Map::Map(std::string mapName)
{
	objects.push_back(new Floor(Point(0, 0), false));
	objects.push_back(new Floor(Point(0, 30), false));

	std::vector<Floor*> endPoints;
	endPoints.push_back(new Floor(Point(60, 60), true));
	endPoints.push_back(new Floor(Point(60, 90), true));
	endPoints.push_back(new Floor(Point(60, 120), true));

	for (int i = 0; i < endPoints.size(); ++i)
	{
		objects.push_back(endPoints[i]);
	}

	std::vector<Box*> boxes;
	boxes.push_back(new Box(Point(30, 60)));
	boxes.push_back(new Box(Point(30, 90)));
	boxes.push_back(new Box(Point(30, 120)));

	for (int i = 0; i < boxes.size(); ++i)
	{
		objects.push_back(boxes[i]);
		movableObjects.push_back(boxes[i]);
	}

	std::vector<Wall*> walls;
	walls.push_back(new Wall(Point(90, 60)));
	walls.push_back(new Wall(Point(90, 90)));
	walls.push_back(new Wall(Point(90, 120)));

	for (int i = 0; i < walls.size(); ++i)
	{
		objects.push_back(walls[i]);
	}

	player = new Player(Point(30, 30), boxes, walls, endPoints);
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