#include "Game.h"
#include "Player.h"
#include "Floor.h"
#include "Box.h"

std::vector<BaseObject> staticObjects;
std::vector<MovableObject> movableObjects;
std::vector<Player> players;

void Game::Start()
{
	Engine::GetInstance()->Initialize(this, "Socoban");

	staticObjects.push_back(Floor(Point(0, 0)));
	staticObjects.push_back(Floor(Point(0, 30)));
	movableObjects.push_back(Box(Point(30, 60)));
	movableObjects.push_back(Box(Point(30, 90)));
	movableObjects.push_back(Box(Point(30, 120)));
	players.push_back(Player(Point(30, 30)));

	Engine::GetInstance()->StartGameLoop();

	Engine::GetInstance()->Exit();
}

void Game::Draw()
{
	for (int i = 0; i < staticObjects.size(); ++i)
	{
		staticObjects[i].Draw();
	}

	for (int i = 0; i < movableObjects.size(); ++i)
	{
		movableObjects[i].Draw();
	}

	for (int i = 0; i < players.size(); ++i)
	{
		players[i].Draw();
	}
}

void Game::Update()
{
	for (int i = 0; i < movableObjects.size(); ++i)
	{
		movableObjects[i].Update();
	}

	for (int i = 0; i < players.size(); ++i)
	{
		players[i].Update();
	}
}

void Game::KeyDownEvent(Key key)
{
	for (int i = 0; i < players.size(); ++i)
	{
		players[i].KeyPressed(key);
	}
}

void Game::KeyUpEvent(Key key)
{
	for (int i = 0; i < players.size(); ++i)
	{
		players[i].KeyReleased(key);
	}
}