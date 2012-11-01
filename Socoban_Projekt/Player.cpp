#include "Player.h"

Player::Player(Point &location)
	: MovableObject(location)
{
	if (animMove.empty())
	{
		LoadBitmaps("right", Key::Right);
		LoadBitmaps("left", Key::Left);
		LoadBitmaps("up", Key::Up);
		LoadBitmaps("down", Key::Down);
		
		bitmap = animMove[(int)Key::Down][0];
		moveDirection = Key::Down;
	}

	pressedKey = Key::None;
	framesCount = 0;
}

void Player::LoadBitmaps(std::string bitmapName, Key key)
{
	std::vector<ALLEGRO_BITMAP*> vector;
	vector.push_back(engine->LoadBMP("player/move/" + bitmapName + "1.bmp"));
	vector.push_back(engine->LoadBMP("player/move/" + bitmapName + "2.bmp"));
	vector.push_back(engine->LoadBMP("player/move/" + bitmapName + "1.bmp"));
	vector.push_back(engine->LoadBMP("player/move/" + bitmapName + "3.bmp"));
	animMove[(int)key] = vector;
}

void Player::Update()
{
	if (!isMoving)
	{
		if (pressedKey == Key::Down || pressedKey == Key::Left
			|| pressedKey == Key::Right || pressedKey == Key::Up)
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
			moveDirection = pressedKey;
		}
		else
		{
			bitmap = animMove[(int)moveDirection][0];
		}
	}
	else
	{
		Anim();
	}

	MovableObject::Update();
}

void Player::Anim()
{
	if (animMove[(int)moveDirection].size() > 0) //zabezpieczenie przed dispose
	{
		bitmap = animMove[(int)moveDirection][(framesCount * animMove[(int)moveDirection].size()) / animFrames];
		++framesCount;
	}
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
	animMove.clear();
}