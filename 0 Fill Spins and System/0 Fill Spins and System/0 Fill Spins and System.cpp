// FillMatrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include<set>
#include<vector>
#include<algorithm>
#include "fileNamePrinter.h"
#include "configReader.h"

const int MaxSpins = 10;
const std::string ConstName = "C";

class Names
{
	std::set<std::string> names;
public:
	void add(std::string name)
	{
		names.insert(name);
	}
	void printToFile(std::ofstream &out,int order)
	{
		
		out << "Var" << order << "={";
		int i=0;
		int amount = names.size();
		for (auto &curName: names)
		{
			out << curName;
			if (i < amount - 1)
				out << ",";
			++i;
		}
		out << "};\n";
	}
};

struct nodePair
{
	int n;
	char c;
	bool operator<(nodePair second)
	{
		if (n<second.n)
			return true;
		else
			return false;
	}
};


void setSingletSpins(int spins[], int Nconf, int size)
{
	for (int j = 0; j<size; j++)
	{		
		spins[j] = Nconf & 1;
		Nconf = Nconf >> 1;
	}
}
void setTripletSpins(int spins[], int Nconf, int size)
{
	int tempSpins[MaxSpins];
	int singletFactor = (int)pow(2, size - 1);
	int curN = Nconf%(singletFactor);
	for (int j = 0; j <size; j++)
	{
		if (curN % 2 == 1)
			tempSpins[j] = 1;
		else
			tempSpins[j] = 0;
		curN = curN / 2;
	}
	int place = (Nconf / singletFactor)/3;
	int type = (Nconf / singletFactor) % 3;
	int cur = 0;
	for (int i = 0; i < size; i++)
	{
		if (i != place)
		{
			spins[i] = tempSpins[cur++];
		}
		else
			spins[i] = 2 + type; //двойка нужна чтобы отличать состо€ни€ триплетов от синглетов
	}
}
///i,j- 1 or 0,   return: 1- sz+,  2-sz-, 3-sp, 4-sm

void setMask(int mask[], int Nconf, int N)//преобразует число в двоичную маску
{
	for (int j = 0; j <= N; j++)
	{
		mask[j] = Nconf & 1;//остаток от делени€ на 2
		Nconf=Nconf >> 1; //деление на 2
	}
}

std::string retTriplet(int i, int j,int num)
{
	char c = '0';
	std::ostringstream s;
	if (i == 0 && j == 0) s << "1";
	if (i == 0 && j == 1) s << "ap" << (char)(c + num);
	if (i == 0 && j == 2) s << "bp" << (char)(c + num);
	if (i == 0 && j == 3) s << "cp" << (char)(c + num);
	if (i == 0 && j == 4) s << "dp" << (char)(c + num);

	if (i == 1 && j == 0) s << "am" << (char)(c + num);
	if (i == 1 && j == 1) s << "aN" << (char)(c + num);//1;
	if (i == 1 && j == 2) s << "am" << (char)(c + num) << "bp" << (char)(c + num);
	if (i == 1 && j == 3) s << "am" << (char)(c + num) << "cp" << (char)(c + num);
	if (i == 1 && j == 4) s << "am" << (char)(c + num) << "dp" << (char)(c + num);

	if (i == 2 && j == 0) s << "bm" << (char)(c + num);
	if (i == 2 && j == 1) s << "bm" << (char)(c + num) << "ap" << (char)(c + num);
	if (i == 2 && j == 2) s << "bN" << (char)(c + num);
	if (i == 2 && j == 3) s << "bm" << (char)(c + num) << "cp" << (char)(c + num);
	if (i == 2 && j == 4) s << "bm" << (char)(c + num) << "dp" << (char)(c + num);

	if (i == 3 && j == 0) s << "cm" << (char)(c + num);
	if (i == 3 && j == 1) s << "cm" << (char)(c + num) << "ap" << (char)(c + num);
	if (i == 3 && j == 2) s << "cm" << (char)(c + num) << "bp" << (char)(c + num);
	if (i == 3 && j == 3) s << "cN" << (char)(c + num);
	if (i == 3 && j == 4) s << "cm" << (char)(c + num) << "dp" << (char)(c + num);

	if (i == 4 && j == 0) s << "dm" << (char)(c + num);
	if (i == 4 && j == 1) s << "dm" << (char)(c + num) << "ap" << (char)(c + num);
	if (i == 4 && j == 2) s << "dm" << (char)(c + num) << "bp" << (char)(c + num);
	if (i == 4 && j == 3) s << "dm" << (char)(c + num) << "cp" << (char)(c + num);
	if (i == 4 && j == 4) s << "dN" << (char)(c + num);
	return s.str();
}

std::string printTripletBilinear(int spins[],int amount,Names &names)
{
	std::ostringstream out;
	std::string opType;
	std::string result;
	out.str("");
	opType = "";
	char c = '0';
	bool first = true;
	for (int i = 0; i < amount; i++)
	{
		out.str("");
		switch (spins[i])
		{
			case 0: continue;//
			case 1:	opType = "a";	break;
			case 2: opType = "b";	break;
			case 3: opType = "c";  break;
			case 4: opType = "d";	break;
		}
		if (!first)
			result+='+';
		first = false;

		out << opType <<"p" << (char)(c + i) << opType <<"m" << (char)(c + i);
		
		names.add(out.str());

		result += out.str();
	}
	return result;
}

int getSingletSpinPairType(int state1, int state2) //возможные матричные элементы
{
	if (state1 == 0 && state2 == 0) return 1;
	if (state1 == 1 && state2 == 1) return 2;
	if (state1 == 1 && state2 == 0) return 3;
	if (state1 == 0 && state2 == 1) return 4;
}

std::string generateSingletName(int res[], int power, bool ifFactor)
///генерирует название дл€ слагаемых которые возможны в этом элементе
{
	std::ostringstream s;

	if (ifFactor) //≈сли надо учесть фактор в матрице коээфициентов, то ищем sz+ и sz-
	{
		double factor = 1;
		for (int l = 0; l<power; l++)
		{
			if (res[l] == 1)
				factor *= 0.5;
			if (res[l] == 2)
				factor *= -0.5;
		}
		s << factor << "*";  //добавл€ем фактор к выходной строке
	}
		
	for (int l = 0; l<power; l++)
	{
		if (res[l]>0)
		{
			if (res[l] == 1 || res[l] == 2) s<< 'z';
			if (res[l] == 3)s<< 'p';
			if (res[l] == 4)s<< 'm';
			s << l;
		}
	}
		
	return s.str();
}



int _tmain(int argc, _TCHAR* argv[])
{
	configReader myConfigReader;
	myConfigReader.openConfigFile("config.txt");
	int order = myConfigReader.readIntWithHeader();//количество спинов
	myConfigReader.closeConfig();

	Names termNames;
		
	int size = (int)pow((double)2, (int)order);

	int *spinsIn = new int[order];
	int *spinsOut = new int[order];
	int *mask = new int[order];
	int *res = new int[order];

	//Write spins order to file
	std::ofstream outSpinsOrder(fileNamePrinter::getPathToSpinsOrder(order), std::ios::out);
	//temp
	std::string tmpS = fileNamePrinter::getPathToSpinsOrder(order);
	//end temp
	for (int i = 0; i < size; i++)
	{
		setSingletSpins(spinsIn, i, order);
		for (int j = 0; j < order; j++)
			outSpinsOrder << spinsIn[j] << " ";
		outSpinsOrder << "\n";
	}
	outSpinsOrder.close();
	//end spins order
	
	std::ofstream outSysAndVars(fileNamePrinter::getPathToSystems(order), std::ios::out);
	int maxOrder = order;
	for (order = 1; order <= maxOrder; order++)
	{
		size = (int)pow((double)2, (int)order);
		std::string s;
		bool flag;
		int amount;

		termNames.add(ConstName);
		outSysAndVars << "Sys" << order << "={";
		std::cout << "size: " << size << "\n";
		for (int i = 0; i < size; i++)
		{
			setSingletSpins(spinsIn, i, order);
			outSysAndVars << "{";
			for (int j = 0; j < size; j++)
			{
				setSingletSpins(spinsOut, j, order);
				s.clear();
				for (int k = 0; k < size; k++)
				{
					setMask(mask, k, order);
					flag = true;
					for (int l = 0; l < order; l++)
						res[l] = 0;
					amount = 0;
					for (int l = 0; l < order; l++)
					{
						int spinPairType = getSingletSpinPairType(spinsOut[l], spinsIn[l]);
						if (mask[l] == 0) //≈сли mask[l]==0 пытаемс€ опустить l-ый член.
															//spinPairType больше двух, значит начальный и конечный спины 
															//в l-ой вершине не совпадают, и опустить член, который ей соответствует нельз€
						{
							if (spinPairType > 2)
							{
								flag = false;
							}
						}
						else
						{
							res[l] = spinPairType;
							amount++;
						}

					}
					if (flag)
					{
						if (amount > 0)
						{
							termNames.add(generateSingletName(res, order, false));
							s += generateSingletName(res, order, true) + "+";
						}
						else
							s += ConstName + "+";
					}
				}
				s += "0";
				if (j == size - 1)
					outSysAndVars << s << "}";
				else
					outSysAndVars << s << ",";

			}
			if (i == size - 1)
				outSysAndVars << "}\n";
			else
				outSysAndVars << ",\n";
		}

		termNames.printToFile(outSysAndVars, order);
	}

	outSysAndVars.close();
	return 0;
}
