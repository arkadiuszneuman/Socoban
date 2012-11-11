#include "Game.h"

void Game::Start()
{
	Engine::GetInstance()->Initialize("Socoban");

	menu = new Menu();
	map = new Map();

	Engine::GetInstance()->AddEvents(this, menu);

	Engine::GetInstance()->StartGameLoop();

	delete map;
	delete menu;

	Engine::GetInstance()->Exit();
}

void Game::Draw()
{
	map->DrawObjects();
	menu->Draw();
}

void Game::Update()
{
	if (!menu->IsFreezed())
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

		menu->Update();
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