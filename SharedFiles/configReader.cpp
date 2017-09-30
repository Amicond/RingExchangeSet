#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "configReader.h"


bool configReader::openConfigFile(std::string configFileName)
{
	config.open(configFileName.c_str(), std::ios::in | std::ios::_Nocreate);
	return !config;
}

void configReader::closeConfig()
{
	config.close();
}

bool configReader::openPointsFile(std::string pointsFileName)
{
	points.open(pointsFileName.c_str(), std::ios::in);
	return !points;
}

void configReader::closePointsFile()
{
	points.close();
}

int configReader::readIntWithHeader()
{
	int res;
	std::string curInputString;
	getline(config, curInputString);//header
	getline(config, curInputString);//values

	inp.str(curInputString);
	inp.clear();
	inp >> res;
	return res;
}

int configReader::readNewlineInt()
{
	int res;
	
	std::string curInputString;
	getline(config, curInputString);
	inp.str(curInputString);
	inp.clear();
	inp >> res;
	return res;
}

int configReader::readNextInt()
{
	int res;
	inp >> res;
	return res;
}

std::string configReader::readStrFromConfig()
{
	std::string str;
	getline(config, str);//header
	getline(config, str);//data
	return str;
}

int configReader::readPoints(std::vector<std::string> &pointsVec)
{
	if (points)
	{
		std::string curPoint;
		while (!points.eof())
		{
			points >> curPoint;
			if (curPoint.length() > 0)
			{
				pointsVec.push_back(curPoint);
			}
		}
	}
	else
	{
		pointsVec.push_back("0.00");
	}
	return pointsVec.size();
}

int configReader::readPoints(std::string fname,std::vector<std::string> &pointsVec)
{
	openPointsFile(fname);	
	int pointsAmount=readPoints(pointsVec);
	closePointsFile();
	return pointsAmount;
}

void configReader::readRouteAmounts(int orderAmounts[][RouteTypeAmount], int minOrder, int maxOrder)
{

	int curOrder;
	std::string curInputString;
	getline(config, curInputString);//header


	for (int i = minOrder; i <= maxOrder; i++)
	{
		getline(config, curInputString);//data
		inp.clear();
		inp.str(curInputString);
		inp >> curOrder;
		if (curOrder != i)
			std::cout << "\n\nAttention!!\n\n";
		else
			for (int j = 0; j < RouteTypeAmount; j++)
				inp >> orderAmounts[i][j];
	}
}