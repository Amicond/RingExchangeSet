// Generate 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileNamePrinter.h"
#include "configReader.h"
#include "ExtendedRoute.h"
#include "RouteOperator.h"

//debug
const bool DEBUG = false;
int generalCounter = 0;
int addCounter = 0;
//end debug
std::ofstream logFile("log.txt", std::ios::out);


void genrateAllExtendedRoutes(std::vector<ExtendedRoute> &routes,ExtendedRoute &curExtendedRoute,int order,std::vector<RouteOperator> &possibleOperators)
{
	static int runCounter = 0;
	runCounter++;
	if (runCounter % 1000 == 0)
		std::cout << runCounter << "\n";
	
	if (DEBUG)
	{
		int level = curExtendedRoute.getSize();
		for (int i = 0; i < level-1; i++)
			logFile << "  ";
		logFile << runCounter <<" level: " << level << " ";
		curExtendedRoute.printRoute(logFile);
		logFile << "\n";
	}

	if (curExtendedRoute.getSize() < order) //if current size less than current order add all possible operators
	{
		std::vector<Point> nodesOfCurRoute;
		for (auto &elem : curExtendedRoute.routeNodes)
			nodesOfCurRoute.push_back(elem.first);
		for (auto &node : nodesOfCurRoute)
		{
			if (DEBUG)
			{
				int level = curExtendedRoute.getSize();
				for (int i = 0; i < level-1; i++)
					logFile << "  ";
				node.print(logFile);
				logFile << "\n";
			}

			for (auto &curOperator : possibleOperators)
			{
				
				curExtendedRoute.addRouteOperator(node, curOperator);
				genrateAllExtendedRoutes(routes, curExtendedRoute, order, possibleOperators);
				curExtendedRoute.removeRouteOperator(node,curOperator);
			}
		}
	}
	else
	{

		bool validConfig = true;
		for (auto &elem : curExtendedRoute.routeNodes)
		{
			if (elem.second < 2)
			{
				validConfig = false;
				break;
			}
		}
		if (validConfig)
		{
			generalCounter++;
			//add check for uniqueness
			if (!curExtendedRoute.ifShadow())
			{
				bool duplicateConfig = false;
				for (auto &goodRoute : routes)
				{
					if (curExtendedRoute.ifSameShape(goodRoute))
					{
						duplicateConfig = true;
						break;
					}
				}
				if (!duplicateConfig)
				{
					if (DEBUG)
					{
						int level = curExtendedRoute.getSize();
						for (int i = 0; i < level-1; i++)
							logFile << "  ";
						logFile << "OK!\n";
						addCounter++;
					}
					routes.push_back(curExtendedRoute);
				}
			}
		}
	}
}

int main()
{
	//new version
	int order = 5;
	std::vector<RouteOperator> allOperators;
	std::vector<ExtendedRoute> allRoutes;
	ExtendedRoute curRoute;
	
	for (int i = 0; i < RouteOperator::getAmountOfBaseOperators(); i++)
	{
		allOperators.push_back(RouteOperator(i));
	}
	int i = 0;
	for (auto &curOperator : allOperators)
	{
		std::cout << "Stage #" << i++<<"\n";
		curRoute.addRouteOperator(Point(0,0),curOperator);
		genrateAllExtendedRoutes(allRoutes, curRoute, order, allOperators);
		curRoute.removeRouteOperator(Point(0,0),curOperator);
	}

	std::ofstream output(fileNamePrinter::getPathToBasicGeneralRoutesInfo(order, std::to_string(0)), std::ios::out);

	for (auto &route : allRoutes)
	{
		route.printRoute(output);
		output << "\n";
	}
	output.close();
	
	
	return 0;
}

