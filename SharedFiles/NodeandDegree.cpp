#include "stdafx.h"
#include "NodeAndDegree.h"


NodeAndDegree::NodeAndDegree()
{
}


NodeAndDegree::~NodeAndDegree()
{
}

bool NodeAndDegree::operator == (const NodeAndDegree &second)const
{
	if (point == second.point&&degree == second.degree)
		return true;
	else
		return false;
}

bool NodeAndDegree::operator < (const NodeAndDegree &second)const
{
	if (point < second.point)
		return true;
	else if (point == second.point)
		if (degree < second.degree)
			return true;
	return false;
}



