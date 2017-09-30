#include "stdafx.h"
#include "Edge.h"


Edge::Edge()
{
	x1 = x2 = y1 = y2 = 0;
}

Edge::Edge(int X1, int Y1, int X2, int Y2)
{
	x1 = X1;
	y1 = Y1;
	x2 = X2;
	y2 = Y2;
}
Edge::Edge(Point p1, Point p2)
{
	x1 = p1.getX();
	y1 = p1.getY();
	x2 = p2.getX();
	y2 = p2.getY();
}
bool Edge::operator==(const Edge &e2)const
{
	if (((x1 == e2.x1) && (x2 == e2.x2) && (y1 == e2.y1) && (y2 == e2.y2)) || ((x1 == e2.x2) && (x2 == e2.x1) && (y1 == e2.y2) && (y2 == e2.y1)))
	{
		return true;
	}
	else
		return false;
}


bool Edge::operator<(const Edge &e2)const
{
	if (x1<e2.x1)
		return true;
	else if (x1 == e2.x1)
	{
		if (y1<e2.y1)
			return true;
		else if (y1 == e2.y1)
		{
			if (x2<e2.x2)
				return true;
			else if (x2 == e2.x2)
			{
				if (y2<e2.y2)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}
void Edge::set(int X1, int Y1, int X2, int Y2)
{
	x1 = X1;
	y1 = Y1;
	x2 = X2;
	y2 = Y2;
}
void Edge::set(Point p1, Point p2)
{
	x1 = p1.getX();
	y1 = p1.getY();
	x2 = p2.getX();
	y2 = p2.getY();
}

void Edge::set(const Edge &e1)
{
	x1 = e1.x1;
	y1 = e1.y1;
	x2 = e1.x2;
	y2 = e1.y2;
}
void Edge::norm()
{
	Point p1(x1, y1);
	Point p2(x2, y2);
	if (p2<p1)
		set(p2, p1);
}

void Edge::centralSymmetry()
{
	x1 *= -1;
	x2 *= -1;
	y1 *= -1;
	y2 *= -1;
}

void Edge::mirrorVerticalAxis()
{
	x1 *= -1;
	x2 *= -1;
}

const Edge operator-(const Edge &e1, const Point &p1)
{
	return Edge(e1.x1 - p1.getX(), e1.y1 - p1.getY(), e1.x2 - p1.getX(), e1.y2 - p1.getY());
}
const Edge operator+(const Edge &e1, const Point &p1)
{
	return Edge(e1.x1 + p1.getX(), e1.y1 + p1.getY(), e1.x2 + p1.getX(), e1.y2 + p1.getY());
}

int Edge::getX1()const
{
	return x1;
}
int Edge::getY1()const
{
	return y1;
}
int Edge::getX2()const
{
	return x2;
}
int Edge::getY2()const
{
	return y2;
}