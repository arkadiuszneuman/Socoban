#include "Game.h"

void Game::Start()
{
	Engine::GetInstance()->Initialize(this, "Socoban");

	map = new Map();
	map->LoadMap("lvl1");

	Engine::GetInstance()->StartGameLoop();

	delete(map);

	Engine::GetInstance()->Exit();
}

void Game::Draw()
{
	map->DrawObjects();
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