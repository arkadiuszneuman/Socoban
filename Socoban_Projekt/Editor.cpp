#include "Editor.h"

Editor::Editor(Map *map)
{
	engine = Engine::GetInstance();

	r = 255;
	g = b = 0;

	buttons.clear();

	buttons.push_back(new Button("save", Point(engine->GetDisplayWidth() - 120, 30), this, true));
	buttons.push_back(new Button("close", Point(engine->GetDisplayWidth() - 120, 70), this, true));

	buttonsDictionary[ObjectType::EWall] = new Button("wall", Point(engine->GetDisplayWidth() - 110, 150), this, false);
	buttonsDictionary[ObjectType::EBox] = new Button("box", Point(engine->GetDisplayWidth() - 65, 150), this, false);
	buttonsDictionary[ObjectType::EDestination] = new Button("destination", Point(engine->GetDisplayWidth() - 110, 190), this, false);
	buttonsDictionary[ObjectType::EFloor] = new Button("floor", Point(engine->GetDisplayWidth() - 65, 190), this, false);
	buttonsDictionary[ObjectType::EPlayer] = new Button("player", Point(engine->GetDisplayWidth() - 85, 230), this, false);
	buttonsDictionary[ObjectType::EEmpty] = new Button("empty", Point(engine->GetDisplayWidth() - 85, 110), this, false);

	bitmap = engine->GetBMP("menu/game2.bmp");

	this->isEnded = false;
	this->player = NULL;
	this->gameWindow = NULL;

	ChangeBrush(ObjectType::EEmpty);
}

void Editor::ChangeBrush(ObjectType objectType)
{
	brush = objectType;
	selectedBrushLocation = buttonsDictionary[objectType]->GetLocation();
}

void Editor::ButtonClicked(std::string name)
{
	if (name == "save")
	{
		gameWindow = new GameWindow(this, "savemap", "ok", "cancel", true);
	}
	if (name == "close")
	{
		this->isEnded = true;
	}
	else if (name == "wall")
	{
		ChangeBrush(ObjectType::EWall);
	}
	else if (name == "box")
	{
		ChangeBrush(ObjectType::EBox);
	}
	else if (name == "destination")
	{
		ChangeBrush(ObjectType::EDestination);
	}
	else if (name == "floor")
	{
		ChangeBrush(ObjectType::EFloor);
	}
	else if (name == "player")
	{
		ChangeBrush(ObjectType::EPlayer);
	}
	else if (name == "empty")
	{
		ChangeBrush(ObjectType::EEmpty);
	}
	else if (name == "windows/ok")
	{
		if (this->gameWindow != NULL)
		{
			if (SaveMap(this->gameWindow->GetText()))
			{
				delete this->gameWindow;
				this->gameWindow = NULL;
			}
		}
	}
	else if (name == "windows/cancel")
	{
		if (this->gameWindow != NULL)
		{
			delete this->gameWindow;
			this->gameWindow = NULL;
		}
	}
}

bool Editor::SaveMap(std::string name)
{
	map->SaveMap(name, floors, destinations, boxes, walls, player);

	return false;
}

bool Editor::IsEnded()
{
	bool ended = this->isEnded;
	this->isEnded = false;

	return ended;
}

void Editor::Draw()
{
	engine->DrawBitmap(bitmap, engine->GetDisplayWidth() - bitmap->GetWidth(), 
		engine->GetDisplayHeight() - bitmap->GetHeight());


	for(std::map<ObjectType, Button*>::iterator it = buttonsDictionary.begin(); it != buttonsDictionary.end(); ++it)
	{
		it->second->Draw();
	}

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->Draw();
	}

	engine->DrawRectangle(selectedBrushLocation.GetX(), selectedBrushLocation.GetY(), selectedBrushLocation.GetX() + BaseObject::TextureSize,
		selectedBrushLocation.GetY() + BaseObject::TextureSize, r, g, b, 3);

	for (int i = 0; i < floors.size(); ++i)
	{
		floors[i]->Draw();
	}

	for (int i = 0; i < destinations.size(); ++i)
	{
		destinations[i]->Draw();
	}

	for (int i = 0; i < boxes.size(); ++i)
	{
		boxes[i]->Draw();
	}

	for (int i = 0; i < walls.size(); ++i)
	{
		walls[i]->Draw();
	}

	if (player != NULL)
	{
		player->Draw();
	}

	if (gameWindow != NULL)
	{
		gameWindow ->Draw();
	}
}

Point Editor::ConvertLogicalToPoint(int x, int y)
{
	x /= BaseObject::TextureSize;
	y /= BaseObject::TextureSize;

	return Point(x * BaseObject::TextureSize, y * BaseObject::TextureSize);
}

void Editor::AddObject(int x, int y, ObjectType objectType)
{
	if (gameWindow == NULL)
	{
		if (objectType == ObjectType::EEmpty)
		{
			RemoveObject(x, y);
		}
		else
		{
			Point point = ConvertLogicalToPoint(x, y);

			for (int x = 0; x < walls.size(); ++x)
			{
				if (walls[x]->GetLocation() == point || (player != NULL && player->GetLocation() == point))
				{
					return;
				}
			}

			for (int x = 0; x < boxes.size(); ++x)
			{
				if (boxes[x]->GetLocation() == point || (player != NULL && player->GetLocation() == point))
				{
					return;
				}
			}

			if (objectType == ObjectType::EFloor || objectType == ObjectType::EDestination)
			{
				for (int x = 0; x < floors.size(); ++x)
				{
					if (floors[x]->GetLocation() == point)
					{
						return;
					}
				}

				for (int x = 0; x < destinations.size(); ++x)
				{
					if (destinations[x]->GetLocation() == point)
					{
						return;
					}
				}
			}

			if (objectType == ObjectType::EPlayer)
			{
				if (player == NULL)
				{
					player = new Player(point);
				}
			}
			else if (objectType == ObjectType::EBox)
			{
				boxes.push_back(new Box(point));
			}
			else if (objectType == ObjectType::EDestination)
			{
				destinations.push_back(new Floor(point, true));
			}
			else if (objectType == ObjectType::EFloor)
			{
				floors.push_back(new Floor(point, false));
			}
			else if (objectType == ObjectType::EWall)
			{
				walls.push_back(new Wall(point));
			}
		}
	}
}

void Editor::RemoveObject(int x, int y)
{
	Point point = ConvertLogicalToPoint(x, y);

	for (int x = 0; x < walls.size(); ++x)
	{
		if (walls[x]->GetLocation() == point)
		{
			delete walls[x];
			walls.erase(walls.begin() + x);
			return;
		}
	}

	for (int x = 0; x < boxes.size(); ++x)
	{
		if (boxes[x]->GetLocation() == point)
		{
			delete boxes[x];
			boxes.erase(boxes.begin() + x);
			return;
		}
	}

	if (player != NULL)
	{
		if (player->GetLocation() == point)
		{
			delete player;
			player = NULL;
		}
	}

	for (int x = 0; x < destinations.size(); ++x)
	{
		if (destinations[x]->GetLocation() == point)
		{
			delete destinations[x];
			destinations.erase(destinations.begin() + x);
			return;
		}
	}

	for (int x = 0; x < floors.size(); ++x)
	{
		if (floors[x]->GetLocation() == point)
		{
			delete floors[x];
			floors.erase(floors.begin() + x);
			return;
		}
	}
}

void Editor::MouseMove(Mouse mouse)
{
}

void Editor::MouseButtonDown(Mouse mouse)
{
	if (mouse.x > 0 && mouse.x < engine->GetDisplayWidth() - bitmap->GetWidth()
		&& mouse.y > 0 && mouse.y < engine->GetDisplayHeight())
	{
		AddObject(mouse.x, mouse.y, brush);
	}
}

void Editor::MouseButtonUp(Mouse mouse)
{
}

void Editor::CharEntered(char c)
{
}

Editor::~Editor()
{
	if (this->gameWindow != NULL)
	{
		delete this->gameWindow;
		this->gameWindow = NULL;
	}

	for(std::map<ObjectType, Button*>::iterator it = buttonsDictionary.begin(); it != buttonsDictionary.end(); ++it)
	{
		delete it->second;
	}

	for (int x = 0; x < buttons.size(); ++x)
	{
		delete buttons[x];
	}

	buttonsDictionary.clear();

	for (int i = 0; i < destinations.size(); ++i)
	{
		delete destinations[i];
	}

	for (int i = 0; i < boxes.size(); ++i)
	{
		delete boxes[i];
	}

	for (int i = 0; i < walls.size(); ++i)
	{
		delete walls[i];
	}

	for (int x = 0; x < floors.size(); ++x)
	{
		delete floors[x];
	}

	if (player != NULL)
	{
		delete player;
	}
}