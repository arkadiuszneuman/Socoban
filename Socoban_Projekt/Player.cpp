#include "Player.h"

Player::Player(Point &location, std::vector<Box*> &boxes, std::vector<Wall*> &walls, std::vector<Floor*> &endPoints)
	: MovableObject(location)
{
	this->boxes = boxes;
	this->walls = walls;
	this->endPoints = endPoints;
	this->animEnded = false;
	this->isEnded = false;

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
	vector.push_back(engine->GetBMP("player/move/" + bitmapName + "1.bmp"));
	vector.push_back(engine->GetBMP("player/move/" + bitmapName + "2.bmp"));
	vector.push_back(engine->GetBMP("player/move/" + bitmapName + "1.bmp"));
	vector.push_back(engine->GetBMP("player/move/" + bitmapName + "3.bmp"));
	animMove[(int)key] = vector;
}

void Player::Update()
{
	if (!isMoving)
	{
		if (animEnded)
		{
			if (CheckEnd())
			{
				isEnded = true;
			}

			animEnded = false;
		}

		if (!isEnded)
		{
			if (pressedKey == Key::Down || pressedKey == Key::Left
				|| pressedKey == Key::Right || pressedKey == Key::Up)
			{
				moveDirection = pressedKey;
				Point playerDestination = GetPointMoveDirection(this->location, pressedKey);

				if (CheckBoxes(playerDestination) && CheckWalls(playerDestination))
				{
					Move(playerDestination);
				}
				else
				{
					bitmap = animMove[(int)moveDirection][0];
				}

				framesCount = 0;
			}
			else
			{
				bitmap = animMove[(int)moveDirection][0];
			}
		}
	}
	else
	{
		Anim();
		if (framesCount == animFrames - 1)
		{
			animEnded = true;
		}
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

bool Player::CheckBoxes(Point playerDestination)
{
	for (int i = 0; i < boxes.size(); ++i)
	{
		if (boxes[i]->GetLocation() == playerDestination)
		{
			//sprawdzanie czy istnieje skrzynka za aktualn¹ skrzynk¹
			for (int x = 0; x < boxes.size(); ++x)
			{
				if (boxes[x]->GetLocation() == GetPointMoveDirection(playerDestination, moveDirection))
				{
					return false;
				}
			}

			//sprawdzanie czy istnieje œciana za skrzynk¹
			if (!CheckWalls(GetPointMoveDirection(boxes[i]->GetLocation(), moveDirection)))
			{
				return false;
			}
			
			//przesuwa s¹siaduj¹c¹ skrzynkê w zale¿noœci od ruchu gracza
			boxes[i]->Move(GetPointMoveDirection(boxes[i]->GetLocation(), moveDirection));

			return true;
		}
	}

	return true;
}

bool Player::CheckWalls(Point destination)
{
	for (int i = 0; i < walls.size(); ++i)
	{
		if (walls[i]->GetLocation() == destination)
		{
			return false;
		}
	}

	return true;
}

bool Player::CheckEnd()
{
	int boxesInPlaces = 0;

	for (int i = 0; i < boxes.size(); ++i)
	{
		for (int x = 0; x < endPoints.size(); ++x)
		{
			if (boxes[i]->GetLocation() == endPoints[x]->GetLocation())
			{
				++boxesInPlaces;
			}
		}
	}

	return boxesInPlaces == endPoints.size();
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