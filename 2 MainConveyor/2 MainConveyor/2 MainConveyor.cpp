//Edit 05.02.2017 First changes from singlet version
//                Change order of basis order
//				  getE0()added
//				  output files names are changed


//edit 08.02.2017 change N->node_num in all "act_*" functions

//edit 08.02.2017  change vIn: read proper file for each route

//edit 09.02.2017 struct states: change array to vector, all act procedures received init for "tempst"

// MainConveyor.cpp : Defines the entry point for the console application.
//

#pragma once
#include "stdafx.h"
#include "configReader.h"
#include "JFactors.h"
#include "MatrixOfResults.h"
#include "Results.h" 
#include "MyFunctions.h"
#include "WFTransformer.h"
#include "fileNamePrinter.h"
#include "ExtendedRoute.h"



const std::string fileNameLog = "log.txt";
const std::string fileNameRouteNums = "input.txt";


int terminateWithError(bool silentMode,int code,std::string message,std::ofstream &logFile)
{
	logFile << message;
	logFile.close();
	if (!silentMode)
	{
		std::cout << "\n\n\n" << message << "\n\n\n";
		int tmp;
		std::cin >> tmp;
	}
	exit(code);
}


int statesAmount(int nodesAmount)
{
	//singlet levels
	return (int)pow(2, nodesAmount);
	//triplet
	//return 3 * (nodesAmount)*(int)pow((double)2, nodesAmount - 1)	
}


int main(int argc, char* argv[])
{

	//public for all threads:

	

	std::ofstream logfile(fileNameLog, std::ios::out);

	std::ifstream terms;//слагаемые ряда теории возмущений
	std::ifstream operatorsset;//ненулевые наборы операторов

	bool silentMode = false;
	int startRouteNum, finRouteNum;

	//private:
	std::ofstream matrixRes;  //выходные файлы
	
	std::vector<point> nodes;//вершины текущего маршрута
	WaveFunction *ref1 = NULL, *ref2 = NULL;

	//check:
	configReader confReader;
	
	std::stringstream fname;
	std::string fileNameString;
	std::istringstream sscanner;

	

	int type, order, subOrder; //Тип маршрутов
	int routesAmount[N + 1][RouteTypeAmount];
	std::vector<int*> nodeSets;
	int *termOrder=NULL;
	int edgeNum;//число ребер в маршруте
	int nodeNum;//число вершин в маршруте

	ExtendedRoute curRoute;



	
	WFTransformer mainTransformer;

	

	std::string outString;
	std::string strType;
	std::string s; //reading from file

	int *curOperatorSet;
	State init;//в будущем для четния
	WaveFunction *wfIn, *wfOut1, *wfOut2;
	WaveFunction wfTemp1, wfTemp2;

	int vecAmount;
	int *procedureOrder;
	int *powerOrder;
	
	MatrixOfResults fullMatrix;
	int realSize;

	int testMode;
	//Read num of first and the last route.
	confReader.openConfigFile(fileNameRouteNums);
	type = confReader.readIntWithHeader();
	order = confReader.readNextInt();
	subOrder = confReader.readNextInt();
	startRouteNum = confReader.readIntWithHeader();
	finRouteNum = confReader.readNextInt();
	testMode = confReader.readIntWithHeader();
	confReader.closeConfig();

	

	confReader.openConfigFile(fileNamePrinter::getPathToConfigFile());
	
	///Error checking
	if (statesAmount(N)>Namount)
		terminateWithError(silentMode, 1, "Change Namount", logfile);
	//Test input data
	if (order > N)
		terminateWithError(silentMode, 3, "\nWrong Const or Config file\n", logfile);
	//Type check
	if(type>=0&&type<3)
        strType=StrType[type];
	else
		terminateWithError(silentMode, 2, "Wrong string type!", logfile);

	//Set params for Jfactors
	JFactors::setOrder(order);
	//reading of route amounts of each type
	confReader.readRouteAmounts(routesAmount, 1, N);
	confReader.closeConfig();

	//Init of arrays for numbers of procedure, and powers of denominators in perturbation series
	procedureOrder = new int[order];
	powerOrder = new int[order];


	

	//считываем все слагаемые для данного порядка
	//отдельно для первого порядка
	if (order == 1)
	{
		termOrder = new int[1];
		termOrder[0] = -1;
		nodeSets.push_back(termOrder);
	}
	else//для всех остальных
	{
		//std::string ttt = fileNamePrinter::getPathToPerturbationTerms(order);
		terms.open(fileNamePrinter::getPathToPerturbationTerms(order), std::ios::in);
		while (!terms.eof())
		{
			getline(terms, s);
			sscanner.clear();
			sscanner.str(s);
			if (s.length() > 0)
			{
				termOrder = new int[order - 1];
				for (int i = 0; i < order - 1; i++)
					sscanner >> termOrder[i];
				nodeSets.push_back(termOrder);
			}
		}
	}
	
	mainTransformer.pairOperator.readMatrixAndEnergie();

	if (testMode) std::cout << "E0 for 2 nodes: " << mainTransformer.pairOperator.getE0(2) << "\n";
		
	//Initializing input and output arrays of WF
	vecAmount =  (int)pow((double)2, order+3);
	wfIn = new WaveFunction[vecAmount];
	wfOut1 = new WaveFunction[vecAmount];
	wfOut2 = new WaveFunction[vecAmount];
	
	//Инициализируем матрицу результатов
	fullMatrix.clearAndSetSize(vecAmount);
	//Конец инициализации;

	curOperatorSet=new int[order];
	procedureOrder=new int[order];
	powerOrder=new int[order];
	
	std::vector<Point> routePoints;
	for(int i=subOrder;i<=subOrder;i++)//Перебираем все возможные длины маршрутов
	{
		for(int j=1;j<=routesAmount[subOrder][type];j++)//перебираем все доступные маршруты при данной длине
		{
			//Блок управления различными копиями, позволяет запускать только часть маршрутов
			if (j > finRouteNum)//если все вычислили, то выходим.
			{
				j = 1 + routesAmount[subOrder][type];
				continue;
			}
			if(j<startRouteNum)
				continue;//пропускаем если не подходит по заданным номерам
			//Конец Блока управления различными копиями

			
			if (DEBUG&&false)
			{
				auto ts = fileNamePrinter::getPathToRouteFile(order, i, j, strType);
				std::ifstream temp(ts, std::ios::in);
				getline(temp, ts);
				int i1, i2, i3;
				temp >> i1>> i2>> i3;
				std::cout << i1 << " " << i2 << " " << i3 << " \n";
				return 0;
			}

			operatorsset.open(fileNamePrinter::getPathToRouteFile(order,i,j,strType), std::ios::in);
			getline(operatorsset,s);
			
			
			operatorsset >> edgeNum >> nodeNum;
			//если это не случай внутреннего оператора, то считываем ребра
			if (edgeNum > 0)
			{				
				curRoute.readRouteFromString(s);
				
				curRoute.evaluateRouteProperties(routePoints);
				
				mainTransformer.clear();
				mainTransformer.setExtendedInteractions(curRoute);			
			}

			//заполняем спины каждый раз
			std::ifstream inStates(fileNamePrinter::getPathToSpinsOrder(nodeNum), std::ios::in);
			
			int curState;

			for (int i = 0; i<vecAmount; i++)
			{
				wfIn[i].clear(nodeNum);
				init.clear();
				for (int j = 0; j<nodeNum; j++) 
				{
					inStates >> curState; 
					init.addClusterState(curState);
				}
				wfIn[i].addEigenState(init);
									
			}
			inStates.close();
			//конец заполнения спинов

			

			getline(operatorsset,s);
			realSize= statesAmount(nodeNum);
			
			fullMatrix.clearAndSetSize(realSize);
			 
			int zz=0;		
			while(!operatorsset.eof())
			{
				getline(operatorsset,s);

				if(s.length()>0)
				{

					std::cout<<order<<" "<<i<<" "<<j<<" zz="<<zz<<"\n";

					zz++;
					sscanner.clear();
					sscanner.str(s);
					for(int k=0;k<order;k++)
					{
						sscanner>>curOperatorSet[k];//считываем n операторов вдоль маршрута
					}
					
					for(unsigned int k=0;k<nodeSets.size();k++)
					{

						for(int ll=0;ll<realSize;ll++)//очищаем выходные данные
						{
							wfOut1[ll].clear(nodeNum);
							wfOut2[ll].clear(nodeNum);
						}
						
						generate_procedure_order(nodeSets[k],curOperatorSet,edgeNum,order,procedureOrder,powerOrder);

						for(int ll=0;ll<realSize;ll++)//вычисляем хвосты. начало
						{
							ref1=&wfIn[ll];
							ref2=&wfTemp1;
							for(int mm=0;mm<(order+1)/2;mm++)
							{
								if(mm==(order+1)/2-1)//если остался последний шаг
									ref2=&wfOut1[ll];
								if(procedureOrder[mm]<=4)//выбираем процедуру
								{
									mainTransformer.actPairMatrix(*ref1, *ref2, curOperatorSet[mm], procedureOrder[mm], powerOrder[mm]);
								}
								else
								{
									mainTransformer.actPairInside(*ref1, *ref2, curOperatorSet[mm] - edgeNum, procedureOrder[mm], powerOrder[mm]);
								}
								
								if(ref2==&wfTemp1)
								{
									ref2=&wfTemp2;
									ref1=&wfTemp1;
									wfTemp2.clear(nodeNum);
								}
								else
								if(ref2==&wfTemp2)
								{
									ref2=&wfTemp1;
									ref1=&wfTemp2;
									wfTemp1.clear(nodeNum);
								}
							}
						}

						///Вычисляем замыкающие хвосты

						for(int ll=0;ll<realSize;ll++)
						{
							ref1=&wfIn[ll];
							ref2=&wfTemp1;
							//для случая первого порядка просто копируем
							if (order == 1)
							{
								mainTransformer.actCopy(wfIn[ll], wfOut2[ll]);
							}
							//для всех остальных порядков
							for(int mm=order-1;mm>order-1-order/2;mm--)
							{
								if (mm == order - order / 2)//если остался последний шаг
								{
									ref2 = &wfOut2[ll];
								}
								
								if (procedureOrder[mm] <= 4)
								{
									mainTransformer.actPairMatrix(*ref1, *ref2, curOperatorSet[mm], procedureOrder[mm], powerOrder[mm]);
								}
								else
								{
									mainTransformer.actPairInside(*ref1, *ref2, curOperatorSet[mm] - edgeNum, procedureOrder[mm], powerOrder[mm]);
								}
								
								if(ref2==&wfTemp1)
								{
									ref2=&wfTemp2;
									ref1=&wfTemp1;
									wfTemp2.clear(nodeNum);
								}else
								if(ref2==&wfTemp2)
								{
									ref2=&wfTemp1;
									ref1=&wfTemp2;
									wfTemp1.clear(nodeNum);
								}
							}
						}

						

						for (int i = 0; i < realSize; i++)
						{
							wfOut1[i].sortWF();
							wfOut2[i].sortWF();
						}

						for(int x=0;x<realSize;x++)
						{
							for(int y=0; y<realSize;y++)
							{
								Results tmpres;
									
								if (DEBUG)
								{
									if (x == 0 && y == 3)
										DEBUGflag = true;
									else
										DEBUGflag = false;
								}
								
								tmpres.scalarProduct(wfOut1[x], wfOut2[y]);

								if(minus1(nodeSets[k],order)==-1)
									tmpres.minus();
								
								fullMatrix.add(x, y, tmpres);
							}
						}
					}
				}
			}
						
			//печать матрицы
			fullMatrix.printMatrix(fileNamePrinter::getPathToResMatrixFiles(strType, order, i, j),order);
			operatorsset.close();
		}
	}

	//finishing
	delete[] curOperatorSet;
	for (auto &elem : nodeSets)
		delete[] elem;

	//if (termOrder != NULL) delete[] termOrder;
	delete [] wfIn;
	delete [] wfOut1;
	delete [] wfOut2;

	delete [] procedureOrder;
	delete [] powerOrder;

	logfile.close();
	if (testMode)
	{
		std::cout << "Cin to exit: ";
		std::cin >> vecAmount;
	}
	return 0;
}