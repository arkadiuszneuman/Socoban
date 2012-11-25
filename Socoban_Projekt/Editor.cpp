#include "Editor.h"

Editor::Editor()
{
	engine = Engine::GetInstance();
	
	r = 255;
	g = b = 0;

	buttons.clear();

	buttons.push_back(Button("save", Point(engine->GetDisplayWidth() - 120, 30), this, true));
	buttons.push_back(Button("close", Point(engine->GetDisplayWidth() - 120, 70), this, true));

	buttonsDictionary[ObjectType::Wall] = new Button("wall", Point(engine->GetDisplayWidth() - 110, 150), this, false);
	buttonsDictionary[ObjectType::Box] = new Button("box", Point(engine->GetDisplayWidth() - 65, 150), this, false);
	buttonsDictionary[ObjectType::Destination] = new Button("destination", Point(engine->GetDisplayWidth() - 110, 190), this, false);
	buttonsDictionary[ObjectType::Floor] = new Button("floor", Point(engine->GetDisplayWidth() - 65, 190), this, false);
	buttonsDictionary[ObjectType::Player] = new Button("player", Point(engine->GetDisplayWidth() - 85, 230), this, false);

	bitmap = engine->GetBMP("menu/game2.bmp");

	this->isEnded = false;
	
	ChangeBrush(ObjectType::Wall);
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
		ChangeBrush(ObjectType::Wall);
	}
	else if (name == "box")
	{
		ChangeBrush(ObjectType::Box);
	}
	else if (name == "destination")
	{
		ChangeBrush(ObjectType::Destination);
	}
	else if (name == "floor")
	{
		ChangeBrush(ObjectType::Floor);
	}
	else if (name == "player")
	{
		ChangeBrush(ObjectType::Player);
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

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].Draw();
	}

	engine->DrawRectangle(selectedBrushLocation.GetX(), selectedBrushLocation.GetY(), selectedBrushLocation.GetX() + BaseObject::TextureSize,
		selectedBrushLocation.GetY() + BaseObject::TextureSize, r, g, b, 3);
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
}