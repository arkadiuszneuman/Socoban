#ifndef POINT_H
#define POINT_H

class Point
{
private:
	float x;
	float y;
public:
	Point();
	Point(float x, float y);
	float GetX();
	float GetY();
	Point operator+(const Point&) const;
	Point operator-(const Point&) const;
	void operator+=(const Point&);
	void operator-=(const Point&);

	bool operator==(const Point&) const;
	bool operator!=(const Point&) const;
};

#endif