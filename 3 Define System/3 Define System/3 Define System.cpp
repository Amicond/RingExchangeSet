// Define Systems.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileNamePrinter.h"
#include "configReader.h"
#include "globalConsts.h"

const bool DEBUG=true;


std::string getSystemNumber(int size)
{
	switch (size)
	{
	case 4:	  return "2";
	case 8:   return "3";
	case 16:  return "4";
	case 32:  return "5";
	case 64:  return "6";
	case 128: return "7";
	case 256: return "8";
	}
}

std::string printVariableNameIn(std::string routeType,int order,int subOrder,int routeNum)
{
	std::ostringstream tmpStr;
	tmpStr << "res" << routeType << "$" << order << "$" << subOrder << "$" << routeNum;
	return tmpStr.str();
}

std::string printVariableNameOut(std::string routeType, int order, int subOrder, int routeNum)
{
	return "Eff"+printVariableNameIn( routeType, order,subOrder,routeNum);
}

void define_term(std::ofstream &math_out, std::string &point, int type, int order, int subOrder, int &total, std::ofstream &out, int term_amount[][RouteTypeAmount], int step,std::vector<int> skips)
{
	std::ostringstream fname, tmpStr;
	std::ifstream cur_f;
	std::string MatrixStr, routeType;
	int size;

	//temp
	std::string tFName;

	for (int j = 1; j <= term_amount[subOrder][type]; j++)
	{

		total++;
		if (total%step == 0)
		{
			out.close();
			tFName = fileNamePrinter::getFileNameOfMathematicaFile(order, point, total / step);
			std::cout << tFName << "\n";
			//добавляем в авто файл
			math_out << "nb1= NotebookOpen[StringJoin[{NotebookDirectory[], \"" << tFName << "\"}]];\n";
			math_out << "NotebookEvaluate[nb1];\n";
			math_out << "NotebookClose[nb1];\n";
			//конец добавки
			out.open(fileNamePrinter::getPathToMathematicaFiles(order, point, total / step) , std::ios::out);
		}
		
		
		routeType = std::to_string(type);
		
		//test version to obtain missed skips files
		//if (find(skips.begin(), skips.end(), j) != skips.end()) //if curNum in skip  list then skip current iteration
		//	continue;

		cur_f.open(fileNamePrinter::getPathToResMatrixFiles(routeType,order,subOrder,j), std::ios::in);
		
		cur_f >> size;
		tmpStr.str("");
		tmpStr << "res" << routeType << "$" << order << "$" << subOrder << "$" << j;
		out << printVariableNameIn(routeType, order, subOrder, j) << "=";
		while (!cur_f.eof())
		{
			getline(cur_f, MatrixStr);
			if (MatrixStr.length()>0)
				out << MatrixStr;
		}
		out << "/.{J1->" << J1 << ",Q->" << point << "};\n";
		out << "If[Max[" << printVariableNameIn(routeType, order, subOrder, j) << "] != Min[" << printVariableNameIn(routeType, order, subOrder, j) << "],\n";
		out << "	" << printVariableNameOut(routeType, order, subOrder, j) << "=Expand[Chop[Solve[Sys";
		
		out << getSystemNumber(size) << "==" << tmpStr.str() << ",Var" << getSystemNumber(size) << "]]];\n";
		out << "	" << "tt = OpenWrite[\""<<  fileNamePrinter::getPathToMathematicaSolutionsFiles(point,routeType,order,subOrder,j) << "\"];\n";
		out << "	" << "If[Length["<<printVariableNameOut(routeType,order,subOrder,j) << "]==0,Write[tt,\"" << order << " " << subOrder << " " << j << "\"];];\n";
		out << "	" << "For[i = 1, i <= Length[" << printVariableNameOut(routeType, order, subOrder, j) << "[[1]]], i++,\n";
		out << "	" << "	 WriteString[tt,";
		out << "ScientificForm[" << printVariableNameOut(routeType, order, subOrder, j) << "[[1, i]], ";
		out << "ExponentFunction -> (If[-100 < # < 10, Null, #] &)], \"\\n\"]";
		out << "];\n";
		out << "	" << "Close[tt];,\n";
		out << "	" << "tt = OpenWrite[\"" << fileNamePrinter::getPathToMathematicaSolutionsFiles(point, routeType, order, subOrder, j) << "\"];\n";
		out << "	" << "Close[tt];\n";
		out << "];\n\n\n";
		cur_f.close();
	}
}

void readSkips(int type,int order,int subOrder,std::vector<int> &skips)
{
	std::ifstream inpSkips(fileNamePrinter::getPathToSkipFiles(TypeStr[type],order,subOrder));
	int curNum;
	while (!inpSkips.eof())
	{
		inpSkips >> curNum;
		skips.push_back(curNum);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int J1 = 1;
	std::vector<std::string> my_points;

	std::string temp;

	std::ofstream out;
	std::ofstream math_out;

	int order, subOrder, mode;
	int amountOfPoints, term_amount[10][RouteTypeAmount];//с запасом

	configReader myConfigReader;

	myConfigReader.openConfigFile("config.txt");
	amountOfPoints = myConfigReader.readIntWithHeader();
	order= myConfigReader.readIntWithHeader();
	mode= myConfigReader.readIntWithHeader();
	myConfigReader.closeConfig();

	myConfigReader.openConfigFile(fileNamePrinter::getPathToConfigFile());
	myConfigReader.readRouteAmounts(term_amount,1,order);
	myConfigReader.closeConfig();

	myConfigReader.openPointsFile("points.txt");
	myConfigReader.readPoints(my_points);
	myConfigReader.closePointsFile();

	
	int total = 0;
	std::ofstream outSystem;

	std::vector<int> skips;

	int step;//количество слагаемых через которое надо начинать новый файл
	for (int jj = 0; jj<amountOfPoints; jj++)//перебираем все точки
	{
	
		math_out.open(fileNamePrinter::getPathToMainMathematicaFiles(my_points[jj],order), std::ios::out);
	
		std::ifstream sysIn(fileNamePrinter::getPathToSystems(order+1), std::ios::in);

		while (!sysIn.eof())
		{
			getline(sysIn, temp);
			if (temp.length()>0)
				math_out << temp << "\n";
		}
		sysIn.close();
		
		math_out << "SetDirectory[NotebookDirectory[]];\n";

		if (mode == 1)//full mode
			subOrder = 1;
		else
			subOrder = order;
		for (; subOrder <= order; subOrder++)
		{
			total = 0;
			if (subOrder<6)
				step = 50;
			else if (subOrder >= 6)
				step = 20;
			
			//добавляем в авто файл

			math_out << "nb1= NotebookOpen[StringJoin[{NotebookDirectory[], \""<< fileNamePrinter::getFileNameOfMathematicaFile(subOrder,my_points[jj], total / step)<< "\"}]];\n";
			math_out << "NotebookEvaluate[nb1];\n";
			math_out << "NotebookClose[nb1];\n";
			//конец добавки

			//for tests
			
			
			out.open(fileNamePrinter::getPathToMathematicaFiles(subOrder, my_points[jj], total / step), std::ios::out);


			for (int i = 1; i <= subOrder; i++)
			{
				std::cout << my_points[jj] << " " << i << " type 0\n";
				
				skips.clear();
				//readSkips(0, order, subOrder, skips);

				if ((i == 1 && subOrder == 1) || (i>1)) //слагаемые с одним оператором возмущения есть только в первом порядке
				{
					define_term(math_out, my_points[jj], 0, subOrder, i, total, out, term_amount, step,skips);
				}
								
			}
			out.close();
		}
		math_out.close();
	}
	return 0;
}

