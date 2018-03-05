// 1.6 Generate Additional Not Loop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "globalConsts.h"
#include "configReader.h"
#include "fileNamePrinter.h"
#include "matrixNodes.h"
#include "ExtendedRoute.h"





void transformPoints(int transformationType, std::vector<Point> &inpPoints, Point shift, std::vector<Point> &outPoints)
//n ������ ��������������� ��� ������� ���������� ������ ����������� � ��������, 
//l ������ �����, ������� ����  �������� � ����� (0,0)
//��� ��������� ������ ���������������  ����� ���� ��������� �������������� ��������� � �������� �������
{
	switch (transformationType)
	{
	case 0:
		for (int i = 0; i < inpPoints.size(); i++) //��������� ������� �� 180
		{
			outPoints.push_back(inpPoints[i]);
			outPoints[i] = outPoints[i] - shift;
		}
		break;
	case 1:
		for (int i = 0; i < inpPoints.size(); i++) //��������� ������� �� 180
		{
			outPoints.push_back(inpPoints[i]);
			outPoints[i].transformRotate();
			outPoints[i] = outPoints[i] - shift;
		}
		break;
	case 2://�������+���������
		for (int i = 0; i < inpPoints.size(); i++)
		{
			outPoints.push_back(inpPoints[i]);
			outPoints[i].transformMirrorY();
			outPoints[i] = outPoints[i] - shift;
		}
		break;
	case 3://�������+���������+�������
		for (int i = 0; i<inpPoints.size(); i++)
		{
			outPoints.push_back(inpPoints[i]);
			outPoints[i].transformMirrorX();
			outPoints[i] = outPoints[i] - shift;
		}
	}
}

void nodesToNumbers(int NNN, std::vector<Point> &curPoints, matrixNodes &matr, std::vector<int> &outputNumbers)
//transfor coordinates to Numbers
{
	int s = matr.getSize() / 2;

	for (auto &curPoint: curPoints)
	{
		outputNumbers.push_back(matr.getElem(curPoint.getX() + s,curPoint.getY() + s));
	}
}

void generateAllVariants(int curOrder, ExtendedRoute &curentRoute, matrixNodes &matr, std::ofstream &out)
{
	std::vector<ExtendedRoute> sameShape;
	ExtendedRoute work;
	std::vector<std::vector<int>>  Nodes;
	std::vector<Point> intitialPoints, transformedPoints;//����� ���������� ���������
	std::vector<Point> shift;//�������������� ������ ��� ������� ��������
	std::vector<int> rotate;//�������������� ��������
	std::vector<int> degrees;//temp vector
	std::vector<bool> ok;

	for (int i = 0; i<4; i++)
	{
		work.copy(curentRoute);
		
		switch (i)
		{
		case 1: work.rotate180(); break;
		case 2: work.rotate180(); work.mirrorVerticalAxis(); break;
		case 3: work.mirrorVerticalAxis(); break;
		}

		intitialPoints.clear();
		degrees.clear();
		
			
		sameShape.push_back(work);
		shift.push_back(Point(0,0));
		rotate.push_back(i);
		ok.push_back(true);
			
	}
	for (int i = 0; i<sameShape.size(); i++)
		sameShape[i].sortOperators();

	for (int i = 0; i<sameShape.size() - 1; i++)
		for (int j = i + 1; j<sameShape.size(); j++)
		{
			if (ok[i] && ok[j])
				if (sameShape[i].operatorCompare(sameShape[j]))
				{
					ok[j] = false;
				}
		}

	intitialPoints.clear();
	
	curentRoute.evaluateRouteProperties(intitialPoints);
	curentRoute.printRoute(out);
	out << "\n";

	std::vector<int> curNum;
	for (int i = 0; i<sameShape.size(); i++)
	{
		curNum.clear();
		transformedPoints.clear();
		if (ok[i])
		{
			transformPoints(rotate[i], intitialPoints, shift[i], transformedPoints);
			nodesToNumbers(curOrder, transformedPoints, matr, curNum);
			
			out << "i ";
			for (int j = 0; j<curNum.size(); j++)
				out << curNum[j] << " ";
			out << "\n";
		}
	}

}

void generateRouteOperators(ExtendedRoute curRoute, int OrderLength, int RouteLength, std::ofstream &outFile)
{
	//standard form: sort edge's nodes and then edges
	curRoute.sortOperators();

	//output of the route
	curRoute.printRoute(outFile);

	//��������� �������� ����� ��������+ ������ ����� - ������� ��� ������ ����� ������ �����������

	std::vector <RouteOperator> uniqueOperators;
	std::vector <int> uniqueOperatorsAmounts;

	std::vector<int> curRouteOperatorAmouts;
	
	std::vector<Point> nodes;
	std::vector<int> amountOfNodes;
	
	
	
	
	
	std::vector<int> curOperatorNums;//������� ����������� ���������� � ���������
	for (int i = 0; i < OrderLength; i++) curOperatorNums.push_back(-1); 

	for (int j = 0; j < OrderLength + 1; j++) curRouteOperatorAmouts.push_back(0);

	RouteOperator cur(0);
	bool flag;
	int realOperatorsLength = 0;//�������� ���������� ��������� "�������" ����������
	int realNodesLength; //�������� ���������� ��������� ������
	

	curRoute.countRouteOperators(uniqueOperators, uniqueOperatorsAmounts, realNodesLength);

	realOperatorsLength = uniqueOperatorsAmounts.size();

	
	int amount = pow((int)(realOperatorsLength + realNodesLength), (int)(OrderLength));//��������� ������������ ���������� ���������� ����������
	int factor = realOperatorsLength + realNodesLength;//�������, ��  ������� �����
	int temp, j;
	outFile << "\n" << realOperatorsLength << " " << realNodesLength << "\n";

	for (int i = 0; i<amount; i++)
	{
		//����������
		temp = i;

		for (j = 0; j < realOperatorsLength; j++)
			curRouteOperatorAmouts[j] = 0;
		flag = true;
		//��������� �� ������ ������� ����������
		for (j = 0; j<OrderLength; j++)
		{
			curOperatorNums[j] = temp%factor;
			temp /= factor;
			if (curOperatorNums[j]<realOperatorsLength)
				curRouteOperatorAmouts[curOperatorNums[j]]++;
		}

		//��������� ������������
		for (j = 0; j<realOperatorsLength; j++)
		{
			if (uniqueOperatorsAmounts[j]>curRouteOperatorAmouts[j])
			{
				flag = false;
				break;
			}
		}
		

		//����, �� � ����
		if (flag)
		{
			for (j = 0; j < OrderLength; j++)
			{
				outFile << curOperatorNums[j] << " ";
			}
			outFile << "\n";
		}
	}

	outFile.close();
}

int _tmain(int argc, _TCHAR* argv[])
{
	int curOrder, subOrder, routeType;
	std::string temp;
	configReader myConfigReader;
	myConfigReader.openConfigFile("conf.txt");
	curOrder = myConfigReader.readIntWithHeader();
	subOrder = myConfigReader.readNextInt();
	routeType = myConfigReader.readNextInt();
	myConfigReader.closeConfig();
	 
	std::string type = TypeStr[routeType];
	
	
	std::ifstream in(fileNamePrinter::getPathToBasicGeneralRoutesInfo(subOrder,type), std::ios::in);
	std::string s;
	ExtendedRoute curRoute;
	
	
	int count = 1;

	matrixNodes myMatrix;
	myMatrix.fillMatrix(curOrder);
	
	std::ofstream out;
	if (curOrder == subOrder)
	{
		out.open(fileNamePrinter::getPathToGeneralRoutesInfo(subOrder, type), std::ios::out);
	}
	
	while (!in.eof())
	{
		getline(in, s);
		if (s.length()>0)
		{
			
			curRoute.readRouteFromString(s);
			curRoute.sortOperators();

			if (curOrder == subOrder)
			{
				generateAllVariants(curOrder, curRoute, myMatrix, out);
			}
				
			std::ofstream outputFileForRoute(fileNamePrinter::getPathToRouteFile(curOrder,subOrder,count++,type), std::ios::out);
			generateRouteOperators(curRoute, curOrder, subOrder, outputFileForRoute);
			outputFileForRoute.close();
		}
	}
	out.close();
	return 0;
}

