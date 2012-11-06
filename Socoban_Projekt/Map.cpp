#include "Map.h"
#include "Player.h"
#include "Wall.h"
#include "Floor.h"
#include "Box.h"

Map::Map()
{
	player = NULL;
}

void Map::LoadMap(std::string mapName)
{
	Dispose();

	//stworzenie i wyzerowanie tablicy mapy
	unsigned short map[22][20];
	for (int i = 0; i <= 21; ++i)
	{
		for (int z = 0; z <= 19; ++z)
		{
			map[i][z] = 0;
		}
	}

	//wczytanie mapy
	std::string path;
	path = "maps/";
	path += mapName;
	path += ".soc";

	FILE *file = fopen(path.c_str(), "rb");
	if(file != NULL) 
	{
		fread(map, sizeof(unsigned short), sizeof(map)/sizeof(unsigned short), file);
		fclose(file);
	}
	else
	{
		Engine::GetInstance()->ShowError("Blad wczytania pliku z mapa.");
		return;
	}

	CreateObjects(map);
}

void Map::CreateObjects(unsigned short map[22][20])
{
	std::vector<Floor*> endPoints;
	std::vector<Box*> boxes;
	std::vector<Wall*> walls;

	//wczytanie obiektów
	for (int i = 0; i <= 21; ++i)
	{
		for (int z = 0; z <= 19; ++z)
		{
			switch (map[i][z])
			{
			case 1:
				walls.push_back(new Wall(Point(i*BaseObject::TextureSize, z*BaseObject::TextureSize)));
				break;
			case 3:
				player = new Player(Point(i*BaseObject::TextureSize, z*BaseObject::TextureSize));
				break;
			case 53:
				endPoints.push_back(new Floor(Point(i*BaseObject::TextureSize,z*BaseObject::TextureSize), true));
				player = new Player(Point(i*BaseObject::TextureSize, z*BaseObject::TextureSize));
				break;
			case 63:
				objects.push_back(new Floor(Point(i*BaseObject::TextureSize,z*BaseObject::TextureSize), false));
				player = new Player(Point(i*BaseObject::TextureSize, z*BaseObject::TextureSize));
				break;
			case 4:
				boxes.push_back(new Box(Point(i*BaseObject::TextureSize, z*BaseObject::TextureSize)));
				break;
			case 5:
				endPoints.push_back(new Floor(Point(i*BaseObject::TextureSize,z*BaseObject::TextureSize), true));
				break;
			case 6:
				objects.push_back(new Floor(Point(i*BaseObject::TextureSize,z*BaseObject::TextureSize), false));
				break;
			case 54:
				boxes.push_back(new Box(Point(i*BaseObject::TextureSize, z*BaseObject::TextureSize)));
				endPoints.push_back(new Floor(Point(i*BaseObject::TextureSize,z*BaseObject::TextureSize), true));
				break;
			case 64:
				boxes.push_back(new Box(Point(i*BaseObject::TextureSize, z*BaseObject::TextureSize)));
				objects.push_back(new Floor(Point(i*BaseObject::TextureSize,z*BaseObject::TextureSize), false));
				break;
			}
		}
	}

	//przepisanie obiektów do odpowiednich kolekcji
	for (int i = 0; i < endPoints.size(); ++i)
	{
		objects.push_back(endPoints[i]);
	}

	for (int i = 0; i < boxes.size(); ++i)
	{
		objects.push_back(boxes[i]);
		movableObjects.push_back(boxes[i]);
	}

	for (int i = 0; i < walls.size(); ++i)
	{
		objects.push_back(walls[i]);
	}

	player->SetBoxes(boxes);
	player->SetWalls(walls);
	player->SetEndpoints(endPoints);

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

bool Map::UpdateObjects()
{
	for (int i = 0; i < movableObjects.size(); ++i)
	{
		movableObjects[i]->Update();
	}

	if (player != NULL)
	{
		return player->IsEnded();
	}

	return true;
}

void Map::KeyPressed(Key key)
{
	if (player != NULL)
	{
		player->KeyPressed(key);
	}
}

void Map::KeyReleased(Key key)
{
	if (player != NULL)
	{
		player->KeyReleased(key);
	}
}

void Map::Dispose()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		delete(objects[i]);
	}

	objects.clear();
	movableObjects.clear();

	player = NULL;
}

Map::~Map()
{
	Dispose();
}