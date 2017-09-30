#include "stdafx.h"
#include "ExtendedRoute.h"



ExtendedRoute::ExtendedRoute()
{
}


ExtendedRoute::~ExtendedRoute()
{
}

int ExtendedRoute::getSize()
{
	return operators.size();
}

void ExtendedRoute::addRouteOperator(Point curPoint, RouteOperator &curRouteOperator)
{
	RouteOperator newOperator(curRouteOperator.getType(),curPoint);
	
	operators.push_back(newOperator);

	auto pointsAndDegres= newOperator.getDegreesOfPoints();
	
	for (auto &elem : pointsAndDegres)
	{
		auto it = routeNodes.find(elem.first);
		if (it != routeNodes.end())
		{ 
			it->second += elem.second;
		}
		else
		{
			routeNodes.insert(elem);
		}
	}
}


//check
void ExtendedRoute::removeRouteOperator(Point curPoint, RouteOperator &curRouteOperator)
{
	RouteOperator routeOp(curRouteOperator.getType(),curPoint);
	auto lastElem = find(operators.begin(),operators.end(),routeOp);
	auto pointAndDegrees = lastElem->getDegreesOfPoints();
	for (auto &elem : pointAndDegrees)
	{
		auto it = routeNodes.find(elem.first);
		if (it != routeNodes.end())
		{
			if (it->second > elem.second)
			{
				it->second -= elem.second;
			}
			else if (it->second==elem.second)
			{
				routeNodes.erase(it);
			}
			else
			{
				std::cout << "\n\nAlarm!!!!!!!!\n\n";
			}
		}
		else
		{
			std::cout << "\n\nAlarm!!!!!!!!\n\n";
		}
	}
	operators.erase(lastElem);
}

void ExtendedRoute::printRoute(std::ostream &out)
{
	for (auto &curOperator : operators)
	{
		curOperator.print(out);
	}
}

bool ExtendedRoute::ifShadow() const// check if current configuration can appears in previous orders
{
	bool flag=false;
	for (auto &operatorToSkip : operators)
	{
		if (count(operators.begin(), operators.end(), operatorToSkip) == 1) 
			continue; //cannot skip operators that occure only once
		else
		{
			flag = true;
			auto allNodes = operatorToSkip.getDegreesOfPoints();
			for (auto &node : allNodes)
			{
				auto res = routeNodes.find(node.first);
				if (res->second - node.second < 2)
				{
					flag = false; //if the configuration invalid without this opertaor
					break;
				}
			}
			if (flag)//if you can skip this operator - than this configuration've already been taken into accout in previous orders
				break;
		}
	}
	return flag;
}

bool ExtendedRoute::ifSameShape(const ExtendedRoute &secondRoute)
{
	if (operators.size() != secondRoute.operators.size())
		return false;

	sort(operators.begin(), operators.end());
	std::vector<RouteOperator> secondOperators(secondRoute.operators);
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 1:
			//mirroring second set
			for (auto &elem : secondOperators)
				elem.verticalAxisReflection();
			break;
		case 2:
			//rotating second set
			for (auto &elem : secondOperators)
				elem.rotate180();
			break;
		case 3:
			//rotating second set
			for (auto &elem : secondOperators)
				elem.verticalAxisReflection();
		default:
			break;
		}
		std::map<Point,int> allPoints;
		for (auto &operatorElem : secondOperators)
		{
			auto points = operatorElem.getDegreesOfPoints();
			for (auto &pointElem : points)
				allPoints.insert(std::pair<Point, int>(pointElem.first, 1));
		}
		Point shiftVector;
		for (auto &curPoint : allPoints)
		{
			shiftVector = curPoint.first;
			for (auto &curOp : secondOperators)
				curOp.moveToPoint(shiftVector);
			sort(secondOperators.begin(), secondOperators.end());
			//direct comparison
			bool flag = true;
			for (int i = 0; i < operators.size(); i++)
			{
				//
				//CHECK IT CHECK IT CHECK IT CHECK IT CHECK IT 
				//CHECK IT CHECK IT CHECK IT CHECK IT CHECK IT 
				//CHECK IT CHECK IT CHECK IT CHECK IT CHECK IT 
				//CHECK IT CHECK IT CHECK IT CHECK IT CHECK IT 
				//
				//if (!(operators[i].compare(secondOperators[i])))
				if (!(operators[i]==secondOperators[i]))
				{
					flag = false;
					break;
				}
			}
			if (flag)
				return true;
			for (auto &curOp : secondOperators)
				curOp.moveToPoint(-shiftVector);
		}
	}
	return false;
}