#include "Game.h"

void Game::Start()
{
	Engine::GetInstance()->Initialize("Socoban");

	menu = new Menu();
	map = new Map();
	map->LoadMap("lvl1");

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
	if (map->UpdateObjects())
	{
		Engine::GetInstance()->endGameLoop = true;
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