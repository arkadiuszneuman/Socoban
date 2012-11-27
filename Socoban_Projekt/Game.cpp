#include "Game.h"

void Game::Start()
{
	Engine::GetInstance()->Initialize("Socoban");

	menu = new Menu();
	map = new Map();
	editor = NULL;

	Engine::GetInstance()->AddEvents(this, this);
	Engine::GetInstance()->StartGameLoop();

	delete map;
	delete menu;

	Engine::GetInstance()->Exit();
}

void Game::Draw()
{
	map->DrawObjects();

	if (!menu->IsInEditor)
	{
		menu->Draw();
	}
	else
	{
		editor->Draw();
	}
}

void Game::Update()
{
	if (!menu->IsFreezed())
	{
		if (!menu->IsInEditor)
		{
			std::string level = menu->GetMap();
			if (level != "")
			{
				map->Dispose();
				if (level != "menu")
				{
					map->LoadMap(level);
				}
			}

			if (map->UpdateObjects())
			{
				menu->NextMap();
			}

			menu->Update(map->GetPlayerSteps());
		}
		else
		{
			if (editor == NULL)
			{
				editor = new Editor();
				Engine::GetInstance()->AddMouseEvent(editor);
			}

			if (editor->IsEnded())
			{
				menu->IsInEditor = false;
				Engine::GetInstance()->RemoveMouseEvent(editor);
				delete editor;
				editor = NULL;
			}
		}
	}
}

void Game::KeyDownEvent(Key key)
{
	map->KeyPressed(key);
}

void Game::KeyUpEvent(Key key)
{
	map->KeyReleased(key);
}

void Game::CharEntered(char c)
{
	menu->CharEntered(c);
}