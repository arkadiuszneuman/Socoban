#include "Player.h"

Player::Player(Point &location, std::vector<Box*> boxes)
	: MovableObject(location)
{
	this->boxes = boxes;

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
			moveDirection = pressedKey;
			Point playerDestination = GetPointMoveDirection(this->location, pressedKey);

			MoveBoxes(playerDestination);
			Move(playerDestination);
			framesCount = 0;
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

Point Player::GetPointMoveDirection(Point point, Key key)
{
	int x = point.GetX(); 
	int y = point.GetY();

	switch (key)
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

	return Point(x, y);
}

void Player::MoveBoxes(Point playerDestination)
{
	for (int i = 0; i < boxes.size(); ++i)
	{
		if (boxes[i]->GetLocation() == playerDestination)
		{
			//przesuwa s¹siaduj¹c¹ skrzynkê w zale¿noœci od ruchu gracza
			boxes[i]->Move(GetPointMoveDirection(boxes[i]->GetLocation(), moveDirection));
		}
	}
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