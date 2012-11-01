#include "Point.h"

Point::Point()
{
}

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Point::GetX()
{
	return x;
}

float Point::GetY()
{
	return y;
}

Point Point::operator+ (const Point& point) const
{
	  int x, y;
	  x = this->x + point.x;
	  y = this->y + point.y;

	  return Point(x, y);
}

Point Point::operator- (const Point& point) const
{
	  int x, y;
	  x = this->x - point.x;
	  y = this->y - point.y;

	  return Point(x, y);
}

void Point::operator+= (const Point& point)
{
	  this->x += point.x;
	  this->y += point.y;
}

void Point::operator-= (const Point& point)
{
	  this->x -= point.x;
	  this->y -= point.y;
}

bool Point::operator== (const Point& point) const
{
	  return this->x == point.x && this->y == point.y;
}

bool Point::operator!= (const Point& point) const
{
	  return this->x != point.x || this->y != point.y;
}