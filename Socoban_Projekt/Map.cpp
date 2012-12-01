#include "Map.h"
#include "Player.h"
#include "Wall.h"
#include "Floor.h"
#include "Box.h"
#include <sstream>
#include <fstream>

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

void Map::SaveMap(std::string mapName, std::vector<Floor*> floors, std::vector<Floor*> destinations, 
		std::vector<Box*> boxes, std::vector<Wall*> walls, Player *player)
{
	std::vector<unsigned short> vmap = CreateArray(floors,destinations, boxes, walls, player);

	unsigned short map[22][20];

	for (int i = 0; i <= 21; ++i)
	{
		for (int z = 0; z <= 19; ++z)
		{
			map[i][z] = vmap[z + (20*i)];
		}
	}

	//zapis mapy
	std::string path;
	path = "maps/";
	path += mapName;
	path += ".soc";

	std::fstream file(path, std::ios::out | std::ios::binary);
	file.write((char*)&map, sizeof(map));
	file.close();

	/*FILE *file = fopen(path.c_str(), "wb");
	if(file == NULL) 
	{
		fwrite(map, sizeof(unsigned short), sizeof(map)/sizeof(unsigned short), file);
		fclose(file);
	}
	else
	{
		Engine::GetInstance()->ShowError("Podana mapa juz istnieje.");
		return;
	}*/
}

std::vector<unsigned short> Map::CreateArray(std::vector<Floor*> floors, std::vector<Floor*> destinations, 
		std::vector<Box*> boxes, std::vector<Wall*> walls, Player *player)
{
	unsigned short map[22][20];

	for (int i = 0; i <= 21; ++i)
	{
		for (int z = 0; z <= 19; ++z)
		{
			map[i][z] = 2;
		}
	}

	for (int i = 0; i < floors.size(); ++i)
	{
		map[(int)(floors[i]->GetLocation().GetX() / 30)][(int)(floors[i]->GetLocation().GetY() / 30)] = 6;
	}

	for (int i = 0; i < destinations.size(); ++i)
	{
		map[(int)(destinations[i]->GetLocation().GetX() / 30)][(int)(destinations[i]->GetLocation().GetY() / 30)] = 5;
	}

	for (int i = 0; i < boxes.size(); ++i)
	{
		if (map[(int)(boxes[i]->GetLocation().GetX() / 30)][(int)(boxes[i]->GetLocation().GetY() / 30)] == 5)
		{
			map[(int)(boxes[i]->GetLocation().GetX() / 30)][(int)(boxes[i]->GetLocation().GetY() / 30)] = 54;
		}
		else if (map[(int)(boxes[i]->GetLocation().GetX() / 30)][(int)(boxes[i]->GetLocation().GetY() / 30)] == 6)
		{
			map[(int)(boxes[i]->GetLocation().GetX() / 30)][(int)(boxes[i]->GetLocation().GetY() / 30)] = 64;
		}
		else
		{
			map[(int)(boxes[i]->GetLocation().GetX() / 30)][(int)(boxes[i]->GetLocation().GetY() / 30)] = 4;
		}
	}

	for (int i = 0; i < walls.size(); ++i)
	{
		map[(int)(walls[i]->GetLocation().GetX() / 30)][(int)(walls[i]->GetLocation().GetY() / 30)] = 1;
	}


	if (map[(int)(player->GetLocation().GetX() / 30)][(int)(player->GetLocation().GetY() / 30)] == 5)
	{
		map[(int)(player->GetLocation().GetX() / 30)][(int)(player->GetLocation().GetY() / 30)] = 53;
	}
	else if (map[(int)(player->GetLocation().GetX() / 30)][(int)(player->GetLocation().GetY() / 30)] == 6)
	{
		map[(int)(player->GetLocation().GetX() / 30)][(int)(player->GetLocation().GetY() / 30)] = 63;
	}
	else
	{
		map[(int)(player->GetLocation().GetX() / 30)][(int)(player->GetLocation().GetY() / 30)] = 3;
	}

	std::vector<unsigned short> vmap;

	for (int i = 0; i <= 21; ++i)
	{
		for (int z = 0; z <= 19; ++z)
		{
			vmap.push_back(map[i][z]);
		}
	}

	return vmap;
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

	return false;
}

int Map::GetPlayerSteps()
{
	if (player != NULL)
	{
		return this->player->GetSteps();
	}
	
	return 0;
}

void Map::Dispose()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		delete objects[i];
	}

	objects.clear();
	movableObjects.clear();

	player = NULL;
}

Map::~Map()
{
	Dispose();
}