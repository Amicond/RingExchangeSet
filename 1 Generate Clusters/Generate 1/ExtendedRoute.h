#pragma once
#include "stdafx.h"
#include "Point.h"
#include "RouteOperator.h"
class ExtendedRoute
{
public:
	std::map<Point, int> routeNodes;
	std::vector<RouteOperator> operators;
	
	int getSize();

	void addRouteOperator(Point curPoint,RouteOperator &curRouteOperator);

	void removeRouteOperator(Point curPoint, RouteOperator &curRouteOperator);
	void printRoute(std::ostream &out);
	

	bool ifSameShape(const ExtendedRoute &secondRoute);
	bool ifShadow()const;// check if current configuration can appears in previous orders
	ExtendedRoute();
	~ExtendedRoute();
};

