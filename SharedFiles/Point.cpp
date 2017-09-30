#include "stdafx.h"
#include "Point.h"

Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Point::set(int x, int y)
{
	this->x = x;
	this->y = y;
}
bool Point::operator==(const Point &p2)const
{
	if ((x == p2.x) && (y == p2.y))
		return true;
	else
		return false;
}

bool Point::operator<(const Point &p2)const
{
	if (x<p2.x)
		return true;
	else if (x == p2.x)
		if (y<p2.y)
			return true;
		else
			return false;
	else
		return false;
}

void Point::transformRotate()
{
	x = -x;
	y = -y;
}
void Point::transformMirrorX()
{
	x = -x;
}
void Point::transformMirrorY()
{
	y = -y;
}

Point Point::operator-()
{
	return Point(-x, -y);
}

const Point operator+(const Point &a, const Point &b)
{
	return Point(a.x + b.x, a.y + b.y);
}
const Point operator-(const Point &a, const Point &b)
{
	return Point(a.x - b.x, a.y - b.y);
}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

void Point::print(std::ostream &out)
{
	out << x << " " << y;
}

