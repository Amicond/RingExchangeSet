#include "stdafx.h"
#include "ExtendedRoute.h"



ExtendedRoute::ExtendedRoute()
{
	sorted = false;
}


ExtendedRoute::~ExtendedRoute()
{
}

int ExtendedRoute::getSize() const
{
	return operators.size();
}

void ExtendedRoute::addRouteOperator(Point curPoint,const RouteOperator &curRouteOperator)
{
	sorted = false;
	RouteOperator newOperator(curRouteOperator);
	
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
	sorted = false;
	RouteOperator routeOp(curRouteOperator.getType(),curPoint);
	auto lastElem = std::find(operators.begin(),operators.end(),routeOp);
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

void ExtendedRoute::printRoute(std::ostream &out) const
{
	for (auto &curOperator : operators)
	{
		curOperator.print(out);
	}
}

void ExtendedRoute::rotate180()
{
	sorted = false;
	std::map<Point, int> newRouteNodes;
	Point tmpPoint;
	for (auto &node : routeNodes)
	{
		tmpPoint=node.first;
		tmpPoint.transformRotate();
		newRouteNodes.insert(std::pair<Point, int>(tmpPoint, node.second));
	}
	routeNodes.clear();
	routeNodes.insert(std::make_move_iterator(newRouteNodes.begin()), std::make_move_iterator(newRouteNodes.end()));
	newRouteNodes.clear();
	for (auto &oper : operators)
		oper.rotate180();
}

void ExtendedRoute::mirrorVerticalAxis()
{
	sorted = false;
	std::map<Point, int> newRouteNodes;
	Point tmpPoint;
	for (auto &node : routeNodes)
	{
		tmpPoint = node.first;
		tmpPoint.transformMirrorY();
		newRouteNodes.insert(std::pair<Point, int>(tmpPoint, node.second));
	}
	routeNodes.clear();
	routeNodes.insert(std::make_move_iterator(newRouteNodes.begin()), std::make_move_iterator(newRouteNodes.end()));
	newRouteNodes.clear();
	for (auto &oper : operators)
		oper.verticalAxisReflection();
}

void ExtendedRoute::shiftPointToZero(Point newInitialPoint)
{
	sorted = false;
	std::map<Point, int> newRouteNodes;
	for (auto &elem : routeNodes)
	{
		newRouteNodes.insert(std::pair<Point, int>(elem.first - newInitialPoint,elem.second));
	}
	routeNodes = newRouteNodes;
	for (auto &elem : operators)
	{
		elem.moveToPoint(newInitialPoint);
	}
}

void ExtendedRoute::countRouteOperators(std::vector<RouteOperator> &uniqueOperators, std::vector<int> &uniqueOperatorsAmount, int &realOperatorsLength) const
{
	uniqueOperators.clear();
	uniqueOperatorsAmount.clear();
	
	std::map<Point, int> uniqueNodes;
	for (auto &curOp : operators)
	{
		auto it = find(uniqueOperators.begin(), uniqueOperators.end(), curOp);
		if (it == uniqueOperators.end())
		{
			uniqueOperators.push_back(curOp);
			uniqueOperatorsAmount.push_back(1);
			auto points=curOp.getDegreesOfPoints();
			for (auto &elem : points)
			{
				if (uniqueNodes.find(elem.first) == uniqueNodes.end())
					uniqueNodes.insert(std::pair<Point, int>(elem.first, 1));
			}
		}
		else
		{
			uniqueOperatorsAmount[std::distance(uniqueOperators.begin(), it)]++;
		}		
	}
	realOperatorsLength = uniqueNodes.size();
}


void ExtendedRoute::evaluateRouteProperties(std::vector<Point> &allRoutePoints) const
{
	//nodes.push_back(point(r[0][0],r[0][1]));
	allRoutePoints.clear();
	for (auto &curPoint : routeNodes)
		allRoutePoints.push_back(curPoint.first);
	sort(allRoutePoints.begin(), allRoutePoints.end());
}

void ExtendedRoute::sortOperators()
{
	if (sorted) return;
	for (auto &elem : operators)
		elem.sortNodes();
	std::sort(operators.begin(), operators.end());
	sorted = true;
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

	sortOperators();
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

void ExtendedRoute::readRouteFromString(std::string input)
{
	sorted = false;
	operators.clear();
	routeNodes.clear();
	std::istringstream iss(input);
	std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>{} };
	for (auto &elem : tokens)
	{
		RouteOperator newOperator(0);
		newOperator.parse(elem);
		addRouteOperator(Point(0,0),newOperator);
	}
}

void ExtendedRoute::copy(const ExtendedRoute &origin)
{
	sorted = origin.sorted;
	routeNodes.clear();
	operators.clear();
	for (auto &node : origin.routeNodes)
		routeNodes.insert(node);
	for (auto &oper : origin.operators)
		operators.push_back(oper);
}

//two routes are comparable if they could be shifted to be identical
bool ExtendedRoute::operatorCompare(const ExtendedRoute &secondRoute)
{
	if (operators.size() != secondRoute.operators.size()) return false;
	//could be rewriten
	Point previousShift(0,0);
	std::vector<Point> secondRoutePoints;
	std::vector<RouteOperator> secondOperators(secondRoute.operators);
	secondRoute.evaluateRouteProperties(secondRoutePoints);
	for (auto &curPoint : secondRoutePoints)
	{
		for (auto &curOp : secondOperators)
			curOp.moveToPoint(curPoint-previousShift); //shift back+new shift simultaneuosly
		sort(secondOperators.begin(), secondOperators.end());
		//direct comparison
		bool flag = true;
		for (int i = 0; i < operators.size(); i++)
		{
			
			if (!(operators[i] == secondOperators[i]))
			{
				flag = false;
				break;
			}
		}
		if (flag)
			return true;
		previousShift = curPoint;//will be previous o the next step
	}
	return false;
}

//two roots are equal if they are identical 
bool ExtendedRoute::isEqual(ExtendedRoute &secondRoute) 
{
	if (operators.size() != secondRoute.operators.size()) return false;
	
	this->sortOperators();
	secondRoute.sortOperators();
	//direct comparison
	
	bool flag = true;
	for (int i = 0; i < operators.size(); i++)
	{
		if (!(operators[i] == secondRoute.operators[i]))
		{
			flag = false;
			break;
		}
	}
	
	return flag;
}