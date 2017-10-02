#include "stdafx.h"
#include "pairOperators.h"


const std::string pairOperators::pairMatrixNames[] = { "SimpleVdiagULJ2MatrElems.txt","SimpleVdiagURJ2MatrElems.txt","SimpleVhorJ1MatrElems.txt","SimpleVhorJ2MatrElems.txt","SimpleVvertJ1MatrElems.txt","SimpleVvertJ2MatrElems.txt"};
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
		s = fileNamePrinter::gePathToPairMatrixes(pairMatrixNames[matrixNum]);
		in.open(s.c_str(), std::ios::in);
		for (int j = 0; j < DiffStates*DiffStates; j++)
		{
			for (int k = 0; k < DiffStates*DiffStates; k++)
			{
				in >> opMatrix[matrixNum][j][k];
				if (opMatrix[matrixNum][k] != 0)
					opMatrixNonZero[matrixNum][j].push_back(std::pair<int, double>(k, opMatrix[matrixNum][j][k]));
			}
		}
		in.close();	
	}

	in.open(fileNamePrinter::gePathToInsideMatrix().c_str(), std::ios::in);
	for (int i = 0; i<DiffStates; i++)
		for (int j = 0; j<DiffStates; j++)
		{
			in >> opMatrixInside[i][j];
			if (opMatrixInside[i][j] != 0)
				opMatrixInsideNonZero[i].push_back(std::pair<int, double>(j, opMatrixInside[i][j]));
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
}


pairOperators::~pairOperators()
{
}
