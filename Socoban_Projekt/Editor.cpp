#include "Editor.h"

Editor::Editor()
{
	engine = Engine::GetInstance();
	
	r = 255;
	g = b = 0;

	buttons.clear();

	buttons.push_back(Button("save", Point(engine->GetDisplayWidth() - 120, 30), this, true));
	buttons.push_back(Button("close", Point(engine->GetDisplayWidth() - 120, 70), this, true));

	buttonsDictionary[ObjectType::EWall] = new Button("wall", Point(engine->GetDisplayWidth() - 110, 150), this, false);
	buttonsDictionary[ObjectType::EBox] = new Button("box", Point(engine->GetDisplayWidth() - 65, 150), this, false);
	buttonsDictionary[ObjectType::EDestination] = new Button("destination", Point(engine->GetDisplayWidth() - 110, 190), this, false);
	buttonsDictionary[ObjectType::EFloor] = new Button("floor", Point(engine->GetDisplayWidth() - 65, 190), this, false);
	buttonsDictionary[ObjectType::EPlayer] = new Button("player", Point(engine->GetDisplayWidth() - 85, 230), this, false);
	buttonsDictionary[ObjectType::EEmpty] = new Button("empty", Point(engine->GetDisplayWidth() - 85, 110), this, false);

	bitmap = engine->GetBMP("menu/game2.bmp");

	this->isEnded = false;
	this->player = NULL;
	
	ChangeBrush(ObjectType::EEmpty);
}

void Editor::ChangeBrush(ObjectType objectType)
{
	brush = objectType;
	selectedBrushLocation = buttonsDictionary[objectType]->GetLocation();
}

void Editor::ButtonClicked(std::string name)
{
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

	//engine->DrawRectangle(engine->GetDisplayWidth() - 82, 118, engine->GetDisplayWidth() - 66, 132, 0, 0, 0, 16);

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].Draw();
	}

	engine->DrawRectangle(selectedBrushLocation.GetX(), selectedBrushLocation.GetY(), selectedBrushLocation.GetX() + BaseObject::TextureSize,
		selectedBrushLocation.GetY() + BaseObject::TextureSize, r, g, b, 3);

	for (int i = 0; i < floors.size(); ++i)
	{
		floors[i]->Draw();
	}

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Draw();
	}

	if (player != NULL)
	{
		player->Draw();
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
	if (objectType == ObjectType::EEmpty)
	{
		RemoveObject(x, y);
	}
	else
	{
		Point point = ConvertLogicalToPoint(x, y);

		for (int x = 0; x < objects.size(); ++x)
		{
			if (objects[x]->GetLocation() == point || (player != NULL && player->GetLocation() == point))
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
			objects.push_back(new Box(point));
		}
		else if (objectType == ObjectType::EDestination)
		{
			floors.push_back(new Floor(point, true));
		}
		else if (objectType == ObjectType::EFloor)
		{
			floors.push_back(new Floor(point, false));
		}
		else if (objectType == ObjectType::EWall)
		{
			objects.push_back(new Wall(point));
		}
	}
}

void Editor::RemoveObject(int x, int y)
{
	Point point = ConvertLogicalToPoint(x, y);

	for (int x = 0; x < objects.size(); ++x)
	{
		if (objects[x]->GetLocation() == point)
		{
			delete objects[x];
			objects.erase(objects.begin() + x);
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
	for(std::map<ObjectType, Button*>::iterator it = buttonsDictionary.begin(); it != buttonsDictionary.end(); ++it)
	{
		it->second->MouseMove(mouse);
	}

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].MouseMove(mouse);
	}
}

void Editor::MouseButtonDown(Mouse mouse)
{
	for(std::map<ObjectType, Button*>::iterator it = buttonsDictionary.begin(); it != buttonsDictionary.end(); ++it)
	{
		it->second->MouseDown(mouse);
	}

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].MouseDown(mouse);
	}

	if (mouse.x > 0 && mouse.x < engine->GetDisplayWidth() - bitmap->GetWidth()
		&& mouse.y > 0 && mouse.y < engine->GetDisplayHeight())
	{
		AddObject(mouse.x, mouse.y, brush);
	}
}

void Editor::MouseButtonUp(Mouse mouse)
{
	for(std::map<ObjectType, Button*>::iterator it = buttonsDictionary.begin(); it != buttonsDictionary.end(); ++it)
	{
		it->second->MouseUp(mouse);
	}

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].MouseUp(mouse);
	}
}

void Editor::CharEntered(char c)
{
	
}

Editor::~Editor()
{
	for(std::map<ObjectType, Button*>::iterator it = buttonsDictionary.begin(); it != buttonsDictionary.end(); ++it)
	{
		delete it->second;
	}

	buttonsDictionary.clear();

	for (int x = 0; x < objects.size(); ++x)
	{
		delete objects[x];
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