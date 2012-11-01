#include "Player.h"

Player::Player(Point &location)
	: MovableObject(location)
{
	if (animMove.empty())
	{
		std::vector<ALLEGRO_BITMAP*> vector;
		vector.push_back(engine->LoadBMP("player/move/right1.bmp"));
		vector.push_back(engine->LoadBMP("player/move/right2.bmp"));
		vector.push_back(engine->LoadBMP("player/move/right3.bmp"));

		animMove[(int)Key::Right] = vector;
		bitmap = vector[0];
	}

	pressedKey = Key::None;
	framesCount = 0;
}

void Player::Update()
{
	if (!isMoving)
	{
		if (pressedKey != Key::None)
		{
			int x = location.GetX(); 
			int y = location.GetY();

			switch (pressedKey)
			{
			case Key::Down:
				y += texSize;
				break;
			case Key::Up:
				y -= texSize;
				break;
			case Key::Left:
				x -= texSize;
				break;
			case Key::Right:
				x += texSize;
				break;
			}

			Move(Point(x, y));
			framesCount = 0;
		}
	}
	else
	{
		++framesCount;
	}

	MovableObject::Update();
}

void Player::KeyPressed(Key key)
{
	if (pressedKey == Key::None)
	{
		pressedKey = key;
	}
}

void Player::KeyReleased(Key key)
{
	if (pressedKey == key)
	{
		pressedKey = Key::None;
	}
}

Player::~Player()
{
	al_destroy_bitmap(bitmap);
	animMove.clear();
}