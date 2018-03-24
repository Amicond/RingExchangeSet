// GeneratePade 2order Terms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iomanip>

#include "configReader.h"
#include "fileNamePrinter.h"



//const string delim = "\\";
//const string out_res = "results";
const char dir_names[] = { 'a', 'b', 'c' };

class st
{
	static const int maxN = 10;
	std::string name;
	double value[maxN];
	int type;
	static bool if_print_operators;
public:
	st()
	{
		type = -1;
		name = "";
		for (int i = 0; i <= maxN; i++)
			value[i] = 0;
	}
	st(std::string termName, double newValue, int curOrder)
	{
		type=setName(termName);
		for (int i = 0; i < maxN; i++)
			value[i] = 0;
		if (0 < curOrder &&curOrder < maxN)
			value[curOrder] = newValue;
	}

	static void setIfPrintOperators(bool ipo)
	{
		if_print_operators = ipo;
	}
	bool setValue(double val, int ind)
	{
		if (ind >= 0 && ind < maxN)
		{
			value[ind] = val;
			return true;
		}
		else
		{
			return false;
		}
	}
	int setName(std::string Name)
	{
		name = Name;
		if (name.length() == 1) return 0; //const-term
		if ((name.length() == 2) && (name[1] = '0')) return 1; //linear term
		if ((name.length() == 4) && (name[1] = '0') && (name[3] < '4')) return 2; //bilinear term
		return -1;
	}
	std::string getName()
	{
		return name;
	}
	double getValue(int ind, bool &status)
	{
		if (ind >= 0 && ind < maxN)
		{
			status = true;
			return value[ind];
		}
		else
		{
			status = false;
			return 0;
		}
	}
	

	bool operator==(st r)
	{
		if (name.compare(r.name) == 0)
			return true;
		else
			return false;
	};

	bool operator==(const std::string newName)const
	{
		return name.compare(newName) == 0;
	}
	bool compare_names(std::string Name)
	{
		return name.compare(Name) == 0;
	}
	void clear()
	{
		for (int i = 0; i < maxN; i++)
			value[i] = 0;
	}
	bool copyValue(st St, int ind)
	{
		if (ind >= 0 && ind < maxN)
		{
			value[ind] = St.value[ind];
			return true;
		}
		else
			return false;
	}

	bool isGoodType()
	{
		return type != -1;
	}
	std::string printLinear()
	{
		if (type == 1)
		{
			std::ostringstream res;
			res << "S" << name[1] << "=";
			if (if_print_operators)
				res << "S" << name[1] << "0 * ";
			res << "{";
			return res.str();
		}
		else
		{
			return "Error!";
		}
	}
	int getDirection()
	{
		if (type == 2)
		{
			return name[3] - '0';
		}
		else
			return -1;
	}

	std::string printBilinear()
	{
		if (type == 2)
		{
			std::ostringstream res;
			res << "J0" << name[3] << name[0] << name[2] << "=";
			if (if_print_operators)
			{
				res << "S" << name[0] << "0 * S" << name[2] << dir_names[getDirection() - 1] << "*";
			}
			res << "{";
			return  res.str();
		}
		else
		{
			return "Error!";
		}
	}

	std::string printTerm(int maxOrder,int precision)
	{
		std::stringstream sstr;
		sstr.precision(precision);
		sstr << std::fixed;
		switch (type)
		{
		case 0:
			sstr << "C= { ";
			break;
		case 1:
			sstr << "S" << name[0] << name[1] << "=";
			if (if_print_operators)
				sstr << "S" << name[0] << name[1] << "0 * ";
			sstr << "{";
			break;
		case 2:
			sstr << "J0" << name[3] << name[0] << name[2] << "=";
			if (if_print_operators)
			{
				sstr << "S" << name[0] << "0 * S" << name[2] << dir_names[getDirection() - 1] << "*";
			}
			sstr << "{";
		}
		for (int j = 1; j <= maxOrder; j++)
		{
			sstr << value[j];
			if (j != maxOrder) sstr << " , ";
		}
		sstr << "};\n";
		return sstr.str();
	}
	
	bool operator<(const st st2)const
	{
		if (type < st2.type)
			return true;
		else
			if (type > st2.type)
				return false;
			else
				return name.compare(st2.name)<0;
	}
};
bool st::if_print_operators=false;

bool ifGoodForPrinting(std::string s)
{
	if (s.length() < 4 || (s.length() == 4 && s[1] == '0'))
		return true;
	else
		return false;
}

std::vector<st> vec_res;




int _tmain(int argc, _TCHAR* argv[])
{

	int maxOrder, points_num, initOrder;
	int precision;
	std::vector<std::string> points;

	configReader myConfigReader;
	
	//read params
	myConfigReader.openConfigFile("config.txt");
	points_num = myConfigReader.readIntWithHeader();
	initOrder = myConfigReader.readIntWithHeader();
	maxOrder = myConfigReader.readNextInt();
	precision = myConfigReader.readIntWithHeader();
	myConfigReader.closeConfig();

	//read points
	myConfigReader.openPointsFile("points.txt");
	myConfigReader.readPoints(points);
	myConfigReader.closePointsFile();

	std::string temp_s;
	std::ostringstream fname;
	std::ofstream results;

	int curPointNum = 0;

	for (auto &curPoint:points)
	{
		auto test = fileNamePrinter::getPathToBilinearSeries(curPoint, maxOrder);
		results.open(fileNamePrinter::getPathToBilinearSeries(curPoint, maxOrder), std::ios::out);

		std::cout << "Point num: " << ++curPointNum << "\n";
		results << "Point: " << curPoint << "\n";
		
		std::ifstream inp;
		double temp_val;
		std::string s;
		std::istringstream iss;
		//st cur_st;

		for (int curOrder = initOrder; curOrder <= maxOrder; curOrder++)
		{
			for (int operatorsAmount = 1; operatorsAmount <= 2; operatorsAmount++)
			{
				std::cout << "  order num: " << curOrder << "\n";
				inp.open(fileNamePrinter::getPathToSumOfTermsNameByOrderAndPoint(curPoint,curOrder, operatorsAmount), std::ios::in);
				
				while (!inp.eof())
				{
					getline(inp, s);
					if (s.length() > 0)
					{
						iss.clear();
						iss.str(s);
						iss >> temp_s >> temp_val;
						if (ifGoodForPrinting(temp_s))
						{
							auto it = find(vec_res.begin(), vec_res.end(), temp_s);
							
							if (it != vec_res.end())
								//element found. update
								it->setValue(temp_val, curOrder);
							else
								//add new element
								vec_res.push_back(st(temp_s, temp_val, curOrder));
						}
					}
				}
				inp.close();
			}
		}


		std::vector<std::string> printableNames;
		for (auto &curTerm : vec_res)
			if (curTerm.isGoodType())
				printableNames.push_back(curTerm.printTerm(maxOrder, precision));
		std::sort(printableNames.begin(), printableNames.end());
		for (auto &curName : printableNames)
			results << curName;
		results.close();
	}
	return 0;
}

