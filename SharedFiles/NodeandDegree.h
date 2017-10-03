#pragma once
#include "Point.h"
class NodeAndDegree 
{
public:

	NodeAndDegree();
	~NodeAndDegree();

	Point point;
	int degree;
	NodeAndDegree(Point p, int d) { point = p; degree = d; };
	bool operator==(const NodeAndDegree &second)const;
	bool operator<(const NodeAndDegree &second)const;
};

