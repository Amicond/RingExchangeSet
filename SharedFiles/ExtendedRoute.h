#ifndef __EXTENDED_ROUTE_H__
#define __EXTENDED_ROUTE_H__

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include "globalConsts.h"
#include "Point.h"
#include "RouteOperator.h"


class ExtendedRoute
{
public:
	std::map<Point, int> routeNodes;
	std::vector<RouteOperator> operators;
	bool sorted;
	
	int getSize()const;

	ExtendedRoute();
	~ExtendedRoute();


	void copy(const ExtendedRoute &origin);
	void addRouteOperator(Point curPoint,const RouteOperator &curRouteOperator);
	void removeRouteOperator(Point curPoint, RouteOperator &curRouteOperator);
	void sortOperators();
	void countRouteOperators(std::vector<RouteOperator> &uniqueOperators, std::vector<int> &uniqueOperatorsAmount, int &realOperatorsLength) const;
	void evaluateRouteProperties(std::vector<Point> &allRoutePoints) const;

	//io
	void readRouteFromString(std::string input);
	void printRoute(std::ostream &out) const;
	

	//transformation
	void rotate180();
	void mirrorVerticalAxis();
	void shiftPointToZero(Point newInitialPoint);//transform all points by rule: point -> point - newInitialPoint

	//checking
	bool ifSameShape(const ExtendedRoute &secondRoute);
	bool ifShadow()const;// check if current configuration can appears in previous orders

	//
	//bool operator==(const ExtendedRoute &secondRoute) const;
	bool operatorCompare(const ExtendedRoute &secondRoute);
	bool isEqual(ExtendedRoute &secondRoute);
};

#endif // !__EXTENDED_ROUTE_H__
