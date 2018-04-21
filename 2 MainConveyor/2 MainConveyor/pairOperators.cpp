#include "stdafx.h"
#include "pairOperators.h"


const std::string pairOperators::pairMatrixNames[] = {"MJhorDoubleTransition.txt","MJvertDoubleTransition.txt","MQhorDoubleTransition.txt","MQvertDoubleTransition.txt","MQhorQuatro1Transition.txt","MQhorQuatro2Transition.txt","MQvertQuatro1Transition.txt","MQvertQuatro2Transition.txt"};

//{ "SimpleVdiagULJ2MatrElems.txt","SimpleVdiagURJ2MatrElems.txt","SimpleVhorJ1MatrElems.txt","SimpleVhorJ2MatrElems.txt","SimpleVvertJ1MatrElems.txt","SimpleVvertJ2MatrElems.txt"};
//const int pairOperators::pairMatrixAmount = 6;

int pairOperators::pairStatesToRow(int s1, int s2, bool inverseOrder)
{
	if (!inverseOrder)
		return s1*DiffStates + s2;
	else
		return s2*DiffStates + s1;
}

void pairOperators::columnToPairStates(int column, int &s1, int &s2, bool inverseOrder)
{
	if (!inverseOrder)
	{
		s1 = column / DiffStates;
		s2 = column%DiffStates;
	}
	else
	{
		s2 = column / DiffStates;
		s1 = column%DiffStates;
	}
}


void pairOperators::readMatrixAndEnergie()
{
	std::ifstream in;
	std::string s = "";
	for (int matrixNum = 0; matrixNum < pairMatrixAmount; matrixNum++)
	{
		s = fileNamePrinter::getPathToPairMatrixes(pairMatrixNames[matrixNum]);
		
		in.open(s.c_str(), std::ios::in);
		
		for (int j = 0; j < DiffStates*DiffStates; j++)
		{
			for (int k = 0; k < DiffStates*DiffStates; k++)
			{
				in >> opMatrix[matrixNum][j][k];
				if (opMatrix[matrixNum][j][k] != 0)
					opMatrixNonZero[matrixNum][j].push_back(std::pair<int, double>(k, opMatrix[matrixNum][j][k]));
			}
		}
		in.close();	
	}

	in.open(fileNamePrinter::gePathToJInsideMatrix().c_str(), std::ios::in);
	for (int i = 0; i<DiffStates; i++)
		for (int j = 0; j<DiffStates; j++)
		{
			in >> opMatrixJInside[i][j];
			if (opMatrixJInside[i][j] != 0)
				opMatrixJInsideNonZero[i].push_back(std::pair<int, double>(j, opMatrixJInside[i][j]));
		}
	in.close();

	//debug
	std::string tmpStr1 = fileNamePrinter::gePathToQInsideMatrix();
	//end debug
	in.open(fileNamePrinter::gePathToQInsideMatrix().c_str(), std::ios::in);
	
	for (int i = 0; i<DiffStates; i++)
		for (int j = 0; j<DiffStates; j++)
		{
			in >> opMatrixQInside[i][j];
			if (opMatrixQInside[i][j] != 0)
				opMatrixQInsideNonZero[i].push_back(std::pair<int, double>(j, opMatrixQInside[i][j]));
		}
	in.close();

	in.open(fileNamePrinter::gePathToEnergies().c_str(), std::ios::in);
	for (int i = 0; i<DiffStates; i++)
	{
		in >> Energie[i];
	}


}

pairOperators::pairOperators()
{
	opMatrix = new double**[pairMatrixAmount];
	for (int i = 0; i < pairMatrixAmount; i++)
	{
		opMatrix[i] = new double*[PairStates];
		for (int j = 0; j < PairStates; j++)
		{
			opMatrix[i][j] = new double[PairStates];
			for (int k = 0; k < PairStates; k++)
			{
				opMatrix[i][j][k] = 0;
			}
		}
	}
}


pairOperators::~pairOperators()
{
}

double pairOperators::getE0(int node_num) {
	return Energie[0] * node_num; //singlet case
}

const double* pairOperators::getEnergiesOfStates()const
{
	return Energie;
}