#ifndef EDGE_H
#define EDGE_H

#include "Point.h"
class Edge
{
	int x1, y1, x2, y2;
public:
	int getX1()const;
	int getY1()const;
	int getX2()const;
	int getY2()const;
	Edge();

	Edge(int X1, int Y1, int X2, int Y2);

	Edge(Point p1, Point p2);
	bool operator==(const Edge &e2)const;


	bool operator<(const Edge &e2)const;
	void set(int X1, int Y1, int X2, int Y2);
	void set(Point p1, Point p2);
	void set(const Edge &e1);
	void norm();
	friend const Edge operator-(const Edge &e1, const Point &p1);
	friend const Edge operator+(const Edge &e1, const Point &p1);
	void centralSymmetry();
	void mirrorVerticalAxis();
};

#endif //!EDGE_H