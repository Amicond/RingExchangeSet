//set of functions to return standard filenames for future use of output files
#pragma once
#include <string>

class fileNamePrinter
{
public:
	//general input 
	static std::string fileNamePrinter::getPathToConfigFile();
	static std::string fileNamePrinter::gePathToMatrixes(std::string matrixPrefix, int vertexNum);
	static std::string fileNamePrinter::gePathToPairMatrixes(std::string matrixName);
	static std::string fileNamePrinter::gePathToInsideMatrix();
	static std::string fileNamePrinter::gePathToEnergies();
	static std::string fileNamePrinter::getPathToPerturbationTerms(int order);

	//output name on stage 0
	static std::string fileNamePrinter::getPathToSpinsOrder(int order);
	static std::string fileNamePrinter::getPathToSystems(int order);
	
	//output name on stage 1
	static std::string fileNamePrinter::getPathToBasicGeneralRoutesInfo(int currentOrder, std::string typeName);
	//output name on stage 1.1
	static std::string fileNamePrinter::getPathToGeneralRoutesInfo(int currentOrder, std::string typeName);
	static std::string fileNamePrinter::getPathToRouteFile(int order, int subOrder, int routeNum, std::string routeType);
	//output name on stage 2
	static std::string getPathToResMatrixFiles(std::string routeType, int currentOrder, int currenSubOrder, int routeNum);
	
	//output on stage 3
	static std::string fileNamePrinter::getFileNameOfMathematicaFile(int order, std::string pointName, int fileNum);
	static std::string fileNamePrinter::getPathToMathematicaFiles(int order, std::string pointName, int fileNum);
	static std::string fileNamePrinter::getPathToMainMathematicaFiles(std::string pointName, int order);
	static std::string fileNamePrinter::getPathToMathematicaSolutionsFiles(std::string pointName, std::string routeType, int order, int subOrder, int routeNum);
	//output name on stage 3.5, after Mathematica

	//input for stage 4
	static std::string getPathToResOfSystemSolving(std::string curJ2Point, int curOrder, int curSuborder, int curRouteNum, std::string typeName);

	//output name on stage 4
	static std::string getPathToSumOfTermsNameByOrderAndPoint(std::string point, int order,int ladderOpAmount);
	
	//output name on stage 5
	static std::string getPathToFourierTransformOfTermsNameByPoint(std::string point, int ladderOpAmount);

};