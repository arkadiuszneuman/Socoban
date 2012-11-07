#include "Player.h"
#include <sstream>

Player::Player(Point &location)
	: MovableObject(location)
{
	this->animEnded = false;
	this->isEnded = false;
	this->showEndAnim = false;

	if (animMove.empty())
	{
		LoadBitmaps("right", Key::Right);
		LoadBitmaps("left", Key::Left);
		LoadBitmaps("up", Key::Up);
		LoadBitmaps("down", Key::Down);
		LoadEndBitmaps();
		
		bitmap = animMove[(int)Key::Down][0];
		moveDirection = Key::Down;
	}

	pressedKey = Key::None;
	framesCount = 0;
}

void Player::LoadBitmaps(std::string bitmapName, Key key)
{
	std::vector<Bitmap*> vector;
	vector.push_back(engine->GetBMP("player/move/" + bitmapName + "1.bmp"));
	vector.push_back(engine->GetBMP("player/move/" + bitmapName + "2.bmp"));
	vector.push_back(engine->GetBMP("player/move/" + bitmapName + "1.bmp"));
	vector.push_back(engine->GetBMP("player/move/" + bitmapName + "3.bmp"));
	animMove[(int)key] = vector;
}

void Player::LoadEndBitmaps()
{
	for (int i = 0; i < 9; ++i)
	{
		std::stringstream out;
		out << i+1;

		std::string path = "player/end/" + out.str() + ".bmp";
		animEnd.push_back(engine->GetBMP(path));
	}
}

void Player::SetBoxes(std::vector<Box*> &boxes)
{
	this->boxes = boxes;
}

void Player::SetWalls(std::vector<Wall*> &walls)
{
	this->walls = walls;
}

void Player::SetEndpoints(std::vector<Floor*> &endPoints)
{
	this->endPoints = endPoints;
}

void Player::Update()
{
	if (!showEndAnim && !isEnded)
	{
		if (!isMoving)
		{
			if (animEnded)
			{
				if (CheckEnd())
				{
					showEndAnim = true;
					framesCount = 0;
				}

				animEnded = false;
			}

			if ((pressedKey == Key::Down || pressedKey == Key::Left
				|| pressedKey == Key::Right || pressedKey == Key::Up) && !showEndAnim)
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
	else if (!isEnded)
	{
		EndAnim();
	}
}

Point Player::GetPointMoveDirection(Point point, Key key)
{
	int x = point.GetX(); 
	int y = point.GetY();

	switch (key)
	{
	case Key::Down:
		y += TextureSize;
		break;
	case Key::Up:
		y -= TextureSize;
		break;
	case Key::Left:
		x -= TextureSize;
		break;
	case Key::Right:
		x += TextureSize;
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

void Player::EndAnim()
{
	int frameToShow = framesCount / 5;

	if (frameToShow == animEnd.size())
	{
		bitmap = 0;
		isEnded = true;
	}
	else
	{
		bitmap = animEnd[frameToShow];
	}

	++framesCount;
}

bool Player::IsEnded()
{
	return this->isEnded;
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
	animEnd.clear();
}