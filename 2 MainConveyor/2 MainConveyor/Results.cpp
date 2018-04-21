#include "stdafx.h"
#include "Results.h"


Results::Results()
{
	for (int i = 0; i < ResAmount; i++)
	{
		factors[i] = 0;
	}
}


Results::~Results()
{
}

double Results::getFactor(int num)const
{
	return factors[num];
}

void Results::setFactor(int num, double value)
{
	factors[num] = value;
}

void Results::addToFactor(int num, double value)
{
	factors[num] += value;
}

Results& Results::operator+=(const Results& tmp)
{
	for (int i = 0; i < ResAmount; i++)
	{
		factors[i] += tmp.factors[i];
	}
	return *this;
}

void Results::minus()
{
	for (int i = 0; i < ResAmount; i++)
		factors[i] *= -1;
}

void  Results::clearForCurrentOrder(int order)
{
	for (int i = 0; i < (order + 2)*(order + 1) / 2; i++)
	{
		factors[i] = 0;
	}
}

void Results::scalarProduct(WaveFunction& wf1, WaveFunction& wf2)
{
	unsigned int i1, i2;
	int tmpres[JFactors::Npowers];
	i2 = 0;// указывает текущую группу
	i1 = 0;// указывает текущую группу
	int last1, last2;
	//debug

	std::ofstream outTest;
	if (DEBUG&&DEBUGflag)
		outTest.open("testOut22.txt", std::ios::out);

	wf1.printWF(outTest);
	outTest << "------------------------\n";
	wf2.printWF(outTest);
	outTest << "------------------------\n";
	//enddebug

	while ((i2<wf2.getEigenstatesAmount()) && (i1<wf1.getEigenstatesAmount()))
	{

		if (wf2.getEigenstateByNumber(i2) == wf1.getEigenstateByNumber(i1))//организуем суммирование
		{

			last1 = wf1.findLastGroup(i1);
			last2 = wf2.findLastGroup(i2);
			for (int i = i1; i <= last1; i++)
			{
				for (int j = i2; j <= last2; j++)
				{
					//складываем степени J-множителей
					if (DEBUG&&DEBUGflag)
					{
						outTest.open("testOut22.txt", std::ios::app);
						outTest << "i1=" << i << " " << "i2=" << j <<" ("<< (int)wf1.getEigenstateByNumber(i).getStateByNumber(0) << " " << (int)wf1.getEigenstateByNumber(i).getStateByNumber(1) << ") (" << (int)wf2.getEigenstateByNumber(j).getStateByNumber(0) << " " << (int)wf2.getEigenstateByNumber(j).getStateByNumber(1)<<")\n";
						outTest.close();
						std::cout<< "i1=" << i << " " << "i2=" << j << "\n";
					}
					for (int ttt = 0; ttt<JFactors::getAmountOfPowers(); ttt++)
					{
						tmpres[ttt] = wf1.getEigenstateByNumber(i).getPowerByNumber(ttt) + wf2.getEigenstateByNumber(j).getPowerByNumber(ttt);
					}

					//преобразуем три степени в номер €чейки массива и заполн€ем ее нужным фактором
					factors[JFactors::getNumberByPowers(tmpres)]+= wf1.getEigenstateByNumber(i).getFactor()*wf2.getEigenstateByNumber(j).getFactor();
				}
			}
			i1 = last1 + 1;
			i2 = last2 + 1;
		}
		else if (wf2.getEigenstateByNumber(i2)<wf1.getEigenstateByNumber(i1))
		{
			i2 = 1 + wf2.findLastGroup(i2);//перешли к следующей группе
		}
		else
		{
			i1 = 1 + wf1.findLastGroup(i1);
		}
	}
	//debug
	//outTest.close();
	//end debug;
}

void Results::print(std::ostream &out)
{
	for (int i = 0; i < ResAmount; i++)
	{
		out << "#" << i << "=" << factors[i] << " ";
	}
	out << "\n";
}