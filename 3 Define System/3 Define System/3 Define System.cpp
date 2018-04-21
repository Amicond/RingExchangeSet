// Define Systems.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileNamePrinter.h"
#include "configReader.h"
#include "globalConsts.h"

//const bool DEBUG=true;


std::string getSystemNumber(int size)
{
	switch (size)
	{
	case 2:	  return "1";
	case 4:	  return "2";
	case 8:   return "3";
	case 16:  return "4";
	case 32:  return "5";
	case 64:  return "6";
	case 128: return "7";
	case 256: return "8";
	}
}

int getPlaquetsAmountByOrder(int order)
{
	switch (order)
	{

	case 1: return 2;
	case 2: return 4;
	case 3: return 5;
	case 4: return 7;
	case 5: return 8; 
	default: std::cout<<"\n\n\n\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAalarm!!!\n\n\n\n";
		std::cin >> order;

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

void addToMainFile(std::ofstream &math_out,std::string &curFileName)
{
	math_out << "nb1= NotebookOpen[StringJoin[{NotebookDirectory[], \"" << curFileName << "\"}]];\n";
	math_out << "NotebookEvaluate[nb1];\n";
	math_out << "NotebookClose[nb1];\n";
}

void addSystemToCurrentFile(std::ofstream &out,std::string &point,std::string variableNameIn, std::string variableNameOut,std::string valJ1, std::string valQ,std::string pathToSolutionFile, int size)
{
	out << "/.{J1->" << valJ1 << ",Q->" << valQ << "};\n";
	out << "If[Max[" << variableNameIn << "] != Min[" << variableNameIn << "],\n";
	out << "	" << variableNameOut << "=Expand[Chop[Solve[Sys";
	out << getSystemNumber(size) << "==" << variableNameIn << ",Var" << getSystemNumber(size) << "]]];\n";
	out << "	" << "tt = OpenWrite[\"" << pathToSolutionFile << "\"];\n";
	out << "	" << "If[Length[" << variableNameOut << "]==0,Write[tt,\"Problem with" << variableNameOut << "\"];];\n";
	out << "	" << "For[i = 1, i <= Length[" << variableNameOut << "[[1]]], i++,\n";
	out << "	" << "	 WriteString[tt,";
	out << "ScientificForm[" << variableNameOut << "[[1, i]], ";
	out << "ExponentFunction -> (If[-100 < # < 10, Null, #] &)], \"\\n\"]";
	out << "];\n";
	out << "	" << "Close[tt];,\n";
	out << "	" << "tt = OpenWrite[\"" << pathToSolutionFile << "\"];\n";
	out << "	" << "Close[tt];\n";
	out << "];\n\n\n";
}

std::string defineStringForInsideMatr(int type)
{
	std::string str;
	std::ostringstream output;
	std::ifstream inpFile;
	double curVal;
	std::string multiplier;
	if (type == 1)
	{
		inpFile.open(fileNamePrinter::gePathToJInsideMatrix(), std::ios::in);
		multiplier = "*(-J1)";
	}
	if (type == 2)
	{
		inpFile.open(fileNamePrinter::gePathToQInsideMatrix(), std::ios::in);
		multiplier = "*Q";
	}

	std::istringstream inpStringParser;
	output << "{{";

	for (int i = 0; i <= 1; i++)
	{
		//read
		getline(inpFile, str);
		//prepare parser
		inpStringParser.clear();
		inpStringParser.str("");
		//load to parse
		inpStringParser.str(str);
		for (int j = 0; j <= 1; j++)
		{
			inpStringParser >> curVal;
			output << curVal << multiplier;
			if (j != 1) output << ",";
		}
		output << "}";
		if (i != 1) output << ",{";
	}
	output << "}";

	return output.str();
}

void define_term(std::ofstream &math_out, std::string &point, int type, int order, int subOrder, int &total, std::ofstream &out, int term_amount[][RouteTypeAmount], int step,std::vector<int> skips)
{
	std::ostringstream fname, tmpStr;
	std::ifstream cur_f;
	std::string MatrixStr, routeType,variableNameIn,variableNameOut;
	int size;

	routeType = std::to_string(type);

	for (int j = 1; j <= term_amount[subOrder][type]; j++)
	{

		total++;
		if (total%step == 0)
		{
			out.close();
			//добавляем в авто файл
			addToMainFile(math_out, fileNamePrinter::getFileNameOfMathematicaFile(order, point, total / step));
			//конец добавки
			out.open(fileNamePrinter::getPathToMathematicaFiles(order, point, total / step) , std::ios::out);
		}
		
		//for new version
		std::string pathToSolutionFile=fileNamePrinter::getPathToMathematicaSolutionsFiles(point, routeType, order, subOrder, j);
		std::string valJ1 = point;
		std::string valQ = "1";
		//end new

		cur_f.open(fileNamePrinter::getPathToResMatrixFiles(routeType,order,subOrder,j), std::ios::in);
		cur_f >> size;
		
		variableNameIn = printVariableNameIn(routeType, order, subOrder, j);
		variableNameOut = printVariableNameOut(routeType, order, subOrder, j);
		out << variableNameIn << "=";
		while (!cur_f.eof())
		{
			getline(cur_f, MatrixStr);
			if (MatrixStr.length()>0)
				out << MatrixStr;
		}
		cur_f.close();
		
		addSystemToCurrentFile(out, point, variableNameIn, variableNameOut, valJ1, valQ, pathToSolutionFile, size);
		/*out << "/.{J1->" << J1 << ",Q->" << point << "};\n";
		out << "If[Max[" << variableNameIn << "] != Min[" << variableNameIn << "],\n";
		out << "	" << variableNameOut << "=Expand[Chop[Solve[Sys";
		out << getSystemNumber(size) << "==" << variableNameIn << ",Var" << getSystemNumber(size) << "]]];\n";
		out << "	" << "tt = OpenWrite[\""<<  fileNamePrinter::getPathToMathematicaSolutionsFiles(point,routeType,order,subOrder,j) << "\"];\n";
		out << "	" << "If[Length["<< variableNameOut << "]==0,Write[tt,\"" << order << " " << subOrder << " " << j << "\"];];\n";
		out << "	" << "For[i = 1, i <= Length[" << variableNameOut << "[[1]]], i++,\n";
		out << "	" << "	 WriteString[tt,";
		out << "ScientificForm[" << variableNameOut << "[[1, i]], ";
		out << "ExponentFunction -> (If[-100 < # < 10, Null, #] &)], \"\\n\"]";
		out << "];\n";
		out << "	" << "Close[tt];,\n";
		out << "	" << "tt = OpenWrite[\"" << fileNamePrinter::getPathToMathematicaSolutionsFiles(point, routeType, order, subOrder, j) << "\"];\n";
		out << "	" << "Close[tt];\n";
		out << "];\n\n\n";*/
		
	}
	
	if (order == 1 && subOrder == 1)
	{
		std::string valJ1 = point;
		std::string valQ = "1";
		size = 2;
		std::string pathToSolutionFile;
		int delta;

		//Jinside
		delta = 1;
		pathToSolutionFile = fileNamePrinter::getPathToMathematicaSolutionsFiles(point, routeType, order, subOrder, term_amount[subOrder][type] + delta);
		variableNameIn = printVariableNameIn(routeType, order, subOrder, term_amount[subOrder][type] + delta);
		variableNameOut = printVariableNameOut(routeType, order, subOrder, term_amount[subOrder][type] + delta);
		out << variableNameIn << "=";
		out << defineStringForInsideMatr(delta);
		addSystemToCurrentFile(out, point, variableNameIn, variableNameOut, valJ1, valQ, pathToSolutionFile, size);

		//Qinside
		delta = 2;
		pathToSolutionFile = fileNamePrinter::getPathToMathematicaSolutionsFiles(point, routeType, order, subOrder, term_amount[subOrder][type] + delta);
		variableNameIn = printVariableNameIn(routeType, order, subOrder, term_amount[subOrder][type] + delta);
		variableNameOut = printVariableNameOut(routeType, order, subOrder, term_amount[subOrder][type] + delta);
		out << variableNameIn << "=";
		out << defineStringForInsideMatr(delta);
		addSystemToCurrentFile(out, point, variableNameIn, variableNameOut, valJ1, valQ, pathToSolutionFile, size);
	}
}

//read inside matrix and convert it to the results in first order


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
	//debug
	//std::string output = defineStringForInsideMatr(1);
	//end debug
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
	
		std::ifstream sysIn(fileNamePrinter::getPathToSystems(getPlaquetsAmountByOrder(order)), std::ios::in);

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

				//if ((i == 1 && subOrder == 1) || (i>1)) //слагаемые с одним оператором возмущения есть только в первом порядке
				{
					define_term(math_out, my_points[jj], 0, subOrder, i, total, out, term_amount, step,skips);
				}

				if (i == 1 && subOrder == 1) //слагаемые с одним оператором возмущения есть только в первом порядке
				{

				}
								
			}
			out.close();
		}
		math_out.close();
	}
	return 0;
}

