#include "Game.h"
#include "Player.h"

Player *player;

void Game::Start()
{
	Engine::GetInstance()->Initialize(this, "Socoban");

	player = new Player(Point(20, 30));

	Engine::GetInstance()->StartGameLoop();

	Engine::GetInstance()->Exit();
}

void Game::Draw()
{
	player->Draw();
}

void Game::Update()
{
	player->Update();
}

void Game::KeyDownEvent(Key key)
{
	player->KeyPressed(key);
}

void Game::KeyUpEvent(Key key)
{
	player->KeyReleased(key);
}