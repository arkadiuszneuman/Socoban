#include "MovableObject.h"

MovableObject::MovableObject(Point &location)
	: BaseObject(location) 
{
	this->destination = location;
	this->isMoving = false;
	this->moveSpeed = 1;
	this->animFrames = 0;
}

void MovableObject::Move(Point destination)
{
	if (!this->isMoving)
	{
		this->destination = destination;
		this->isMoving = true;

		if (abs(this->location.GetX() - destination.GetX()) > abs(this->location.GetY() - destination.GetY()))
		{
			this->animFrames = abs(this->location.GetX() - destination.GetX()) / moveSpeed;
		}
		else
		{
			this->animFrames = abs(this->location.GetY() - destination.GetY()) / moveSpeed;
		}
	}
}

void MovableObject::Update()
{
	if (this->isMoving)
	{
		float x = 0;
		float y = 0;

		x = CalcMoveSpeed(this->location.GetX(), destination.GetX());
		y = CalcMoveSpeed(this->location.GetY(), destination.GetY());

		location += Point(x, y);

		if (location == destination)
		{
			this->isMoving = false;
			this->animFrames = 0;
		}
	}
}

float MovableObject::CalcMoveSpeed(float location, float destination)
{
	float move;

	if (abs(location - destination) < moveSpeed)
	{
		move = abs(location - destination); //stworzone, aby przesuwany obiekt nie kr¹¿y³ wokó³ punktu docelowego
	}
	else
	{
		move = moveSpeed;
	}

	if (location > destination)
	{
		move *= -1;
	}

	return move;
}