#ifndef __NODE_AND_DEGREE_H__
#define __NODE_AND_DEGREE_H__


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

#endif // !__NODE_AND_DEGREE_H__