#include "Game.h"

void Game::Start()
{
	Engine::GetInstance()->Initialize(this, "Socoban");

	map = new Map("ss");

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
	map->UpdateObjects();
}

void Game::KeyDownEvent(Key key)
{
	map->KeyPressed(key);
}

void Game::KeyUpEvent(Key key)
{
	map->KeyReleased(key);
}