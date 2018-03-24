// 9 Collect Third Terms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



//global
#include "globalConsts.h"
#include "configReader.h" 
#include "matrixNodes.h"
#include "fileNamePrinter.h"
#include "Term.h"
#include "matrixNodes.h"

//local
#include "localConsts.h"
#include "aOperators.h"
#include "cos.h"

int main(int argc, char * argv[])
{
	//config  vars
	int minOrder, maxOrder;
	std::vector<std::string> points;
	int ladderOpAmount;

	//config init
	configReader myConfReader;
	myConfReader.openConfigFile("config.txt");

	//read parameters
	minOrder=myConfReader.readIntWithHeader();
	maxOrder = myConfReader.readNextInt();
	ladderOpAmount = myConfReader.readIntWithHeader();

	//close config
	myConfReader.closeConfig();

	//read points
	myConfReader.readPoints("points.txt",points);
	
	//input file name
	std::string fName;
	
	//input string with term info
	std::string inputLine;
	std::string inputTerm;
	std::istringstream inputLineParser;
	
	//var to read and store cordinate term
	Term currentTerm;

	//var to performe, to store and print result of Fourier transform 
	bilinearFourierLadderOperators currentFourierOperator;
	
	//init Matrix and Cos::class
	matrixNodes matrix;
	matrix.fillMatrix(maxOrder);
	Cos::set(matrix.getMatrix(), matrix.getSize());

	for (auto &elem : points)
	{
		fName = fileNamePrinter::getPathToFourierTransformOfTermsNameByPoint(elem, ladderOpAmount);
		std::ofstream out(fName, std::ios::out);
		out << "{";
		for (int curOrder = minOrder; curOrder <= maxOrder; curOrder++)
		{
			std::cout << elem<<" "<< curOrder << "\n";
			fName = fileNamePrinter::getPathToSumOfTermsNameByOrderAndPoint(elem, curOrder, ladderOpAmount);
			std::ifstream inputTermsFile(fName, std::ios::in);
			
			bool firstTerm = true;//to decided if plus sing should be print
			while (!inputTermsFile.eof())
			{
				
				//read term name
				getline(inputTermsFile,inputLine);
				if (inputLine.length() > 0)
				{
					if (firstTerm)
						firstTerm = false;
					else
						out << "+";
					inputLineParser.clear();
					inputLineParser.str(inputLine);
					inputLineParser >> inputTerm;
					//parse term
					currentTerm.parseTerm(inputTerm);
					// Fourier transform into momentum representation
					bool transformationSuccess = currentFourierOperator.convertTerm(currentTerm);
					if (!transformationSuccess)
					{
						int temp;
						std::cout << "Alarm!!!!!!";
						std::cin >> temp;
					}
					//read coeff
					inputLineParser >> currentFourierOperator.coefficient_;
					//print Fourier to file
					currentFourierOperator.printAterm(out);
				}
			}
			if (curOrder != maxOrder)
				out << ",";
		}
		out << "}";
		out.close();
	}
	return 0;
}

