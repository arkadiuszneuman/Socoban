#include "Game.h"
#include "Button.h"
Button *b;

void Game::Start()
{
	Engine::GetInstance()->Initialize(this, "Socoban");

	map = new Map();
	map->LoadMap("lvl1");

	b = new Button("End", Point(0, 0));

	Engine::GetInstance()->StartGameLoop();

	delete(map);

	Engine::GetInstance()->Exit();
}

void Game::Draw()
{
	map->DrawObjects();
	b->Draw();
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

void Game::MouseMove(Mouse mouse)
{
	b->MouseMove(mouse);
}

void Game::MouseButtonDown(Mouse mouse)
{
	b->MouseDown(mouse);
}

void Game::MouseButtonUp(Mouse mouse)
{
	b->MouseUp(mouse);
}