//Modifications:
// 13.05.2017 

//global include
#include "stdafx.h"
#include "globalConsts.h"
#include "configReader.h"
#include "LadderOperator.h"
#include "Term.h"
#include "fileNamePrinter.h"
#include "ExtendedRoute.h"
#include "Point.h"
//local include
//#include "localConsts.h"

#include "Summator.h"




class OutputFilePreparator
{
	int ladderOpLength_;

public:
	OutputFilePreparator(int _ladderOpLength)
	{
		ladderOpLength_ = _ladderOpLength;
	}


	void  openFile(std::ofstream &outResFile, int order, std::string point)
	{
		if (outResFile)
			outResFile.close();
		outResFile.open(fileNamePrinter::getPathToSumOfTermsNameByOrderAndPoint(point,order,ladderOpLength_), std::ios::out);
		outResFile.setf(std::ios::fixed);
		outResFile << std::setprecision(10);
	}

};


void sumTerms(int order, int ordernums[][RouteTypeAmount], std::string curPoint, int opLength,bool fullSummation)
//fullSummation: true if we consider all translational-invariant terms. Divide "C" (constant term) by the length of the route
//fullSummation: true if we consider only  translationally different terms. Just sum all avaliable "C" (constant term)
{
	std::ostringstream str;
	std::string s;
	std::string curResFileName;
	std::ifstream termsAndNodes;
	std::ifstream resFile;
	
	//to parse route and determine nodes order
	ExtendedRoute curExtendedRoute; 
	std::vector<Point> routeNodes;


	int curRouteNum;
	int subOrder;

	Term curTerm;
	Summator summator(opLength);

	for (int type = 0; type < RouteTypeAmount; type++)
	{
		curRouteNum = 1;
		subOrder = minSubOrder[type];
		
		//for type zero fisrt suborder exists only in 1st order
		

		while (subOrder <= order)
		{
			termsAndNodes.close();
			termsAndNodes.open(fileNamePrinter::getPathToGeneralRoutesInfo(subOrder, TypeStr[type]), std::ios::in);
			
			//debug
			if (DEBUG)
				std::string tmpStr = fileNamePrinter::getPathToGeneralRoutesInfo(subOrder, TypeStr[type]);
			//end debug
			
			while (!termsAndNodes.eof())
			{
				getline(termsAndNodes, s);
				if (s.length() > 0)
				{
					if (s[0] != 'i')//new route
					{
						std::cout << "order: " << order << "suborder: " << subOrder << "curRouteNum: " << curRouteNum << "\n";

						curExtendedRoute.readRouteFromString(s);
						curExtendedRoute.evaluateRouteProperties(routeNodes);
						summator.parseNewRoute(routeNodes.size());
						
						//debug
						if (DEBUG)
						{
							Summator::out_ << "order: " << order << "suborder: " << subOrder << "curRouteNum: " << curRouteNum << "\n";
						}
						//end debug
						curResFileName = fileNamePrinter::getPathToMathematicaSolutionsFiles(curPoint, TypeStr[type], order, subOrder, curRouteNum, false);
						
						curRouteNum++;
						
					}
					else //new set of nodes for current route
					{
						summator.parseNodes(s,true);
						s = "";
						resFile.open(curResFileName, std::ios::in);
						while (!resFile.eof())
						{
							getline(resFile, s);
							if (s.length() > 0)
								summator.addTerm(s,fullSummation);
						}
						resFile.close();
					}
				}
			}
			//special case for inside op
			if (order == 1 && subOrder == 1)
			{
				summator.parseNewRoute(1);
				curResFileName = fileNamePrinter::getPathToMathematicaSolutionsFiles(curPoint, TypeStr[type], order, subOrder, curRouteNum, false);
				summator.parseNodes("i 0", true);
				s = "";
				resFile.open(curResFileName, std::ios::in);
				while (!resFile.eof())
				{
					getline(resFile, s);
					if (s.length() > 0)
						summator.addTerm(s,fullSummation);
				}
				resFile.close();
			}
			subOrder++;
			curRouteNum = 1;
		}
	}

	std::ofstream out;
	OutputFilePreparator ofp(opLength);
	ofp.openFile(out, order, curPoint);
	summator.print(out);
	out.close();
	
}



int _tmain(int argc, _TCHAR* argv[])
{	
	std::ofstream tmpout(testOutput, std::ios::out);
	tmpout.close();
	Summator::out_;
	int pointsAmount, order;
	int rotesAmounts[MaxOrder][RouteTypeAmount];
	bool fullSummation;
	std::vector<std::string> points;
	
	std::string inputPathToResFiles;

	int sOperators;

	configReader myConfigReader;

	myConfigReader.openConfigFile("config.txt");

	order = myConfigReader.readIntWithHeader();//max order of current run
	sOperators= myConfigReader.readIntWithHeader();//max of ladder operators in output term
	fullSummation = myConfigReader.readIntWithHeader();
	myConfigReader.closeConfig();

	myConfigReader.openConfigFile(fileNamePrinter::getPathToConfigFile());
	myConfigReader.readRouteAmounts(rotesAmounts, 1, order);
	myConfigReader.closeConfig();
		
	pointsAmount=myConfigReader.readPoints("points.txt",points);

	for (int point_num = 0; point_num<pointsAmount; point_num++)
	{
		std::cout << "point: " << points[point_num] << "\n";
		for (int curOrder = 1; curOrder <= order;curOrder++)
			sumTerms(curOrder, rotesAmounts, points[point_num], sOperators,fullSummation);
	}
	if (DEBUG)
	{
		Summator::out_.close();
		std::cin >> order;
	}
	return 0;
}

