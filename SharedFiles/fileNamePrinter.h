//set of functions to return standard filenames for future use of output files
#ifndef __FILE_NAME_PRINTER_H__
#define __FILE_NAME_PRINTER_H__
#include <string>

class fileNamePrinter
{
public:
	//general input 
	static std::string getPathToConfigFile();
	static std::string gePathToMatrixes(std::string matrixPrefix, int vertexNum);
	static std::string getPathToPairMatrixes(std::string matrixName);
	static std::string gePathToJInsideMatrix();
	static std::string gePathToQInsideMatrix();
	static std::string gePathToEnergies();
	static std::string getPathToPerturbationTerms(int order);

	//output name on stage 0
	static std::string getPathToSpinsOrder(int order);
	static std::string getPathToSystems(int order);
	
	//output name on stage 1
	static std::string getPathToBasicGeneralRoutesInfo(int currentOrder, std::string typeName);
	//output name on stage 1.1
	static std::string getPathToGeneralRoutesInfo(int currentOrder, std::string typeName);
	static std::string getPathToRouteFile(int order, int subOrder, int routeNum, std::string routeType);
	//output name on stage 2
	static std::string getPathToResMatrixFiles(std::string routeType, int currentOrder, int currenSubOrder, int routeNum);
	
	//output name on stage 2.5/
	static std::string getPathToSkipFiles(std::string routeType, int currentOrder, int currenSubOrder);

	//output on stage 3
	static std::string getFileNameOfMathematicaFile(int order, std::string pointName, int fileNum);
	static std::string getPathToMathematicaFiles(int order, std::string pointName, int fileNum);
	static std::string getPathToMainMathematicaFiles(std::string pointName, int order);
	static std::string getPathToMathematicaSolutionsFiles(std::string pointName, std::string routeType, int order, int subOrder, int routeNum, bool mathematicaOutput=true);
	//output name on stage 3.5, after Mathematica

	//input for stage 4
	//static std::string getPathToResOfSystemSolving(std::string curJ2Point, int curOrder, int curSuborder, int curRouteNum, std::string typeName);

	//output name on stage 4
	static std::string getPathToSumOfTermsNameByOrderAndPoint(std::string point, int order,int ladderOpAmount);

	//output name on stage 4.4
	static std::string getPathToBilinearSeries(std::string point, int maxOrder);
	
	//output name on stage 5
	static std::string getPathToFourierTransformOfTermsNameByPoint(std::string point, int ladderOpAmount);

};

#endif //__FILE_NAME_PRINTER_H__