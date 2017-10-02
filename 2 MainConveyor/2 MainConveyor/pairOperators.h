#pragma once

#include "Consts.h"
#include "fileNamePrinter.h"
class pairOperators
{
public:
	static const std::string pairMatrixNames[]; //array of names of operators that act on two plaquet simultaneously
	//include J2-diag-UR, J2-diag-UL, J1-hor, J2-hor, J1-vert, J2-vert
	static const int pairMatrixAmount = 6;//must be consistent with previous array

	void readMatrixAndEnergie();
	double opMatrix[pairMatrixAmount][DiffStates*DiffStates][DiffStates*DiffStates];
	double opMatrixInside[DiffStates][DiffStates];

	std::vector<std::pair<int, double>> opMatrixNonZero[pairMatrixAmount][DiffStates*DiffStates];
	std::vector<std::pair<int, double>> opMatrixInsideNonZero[DiffStates];

	
	double Energie[DiffStates*DiffStates]; //Energie of plaquett's eigenstates
	
	static int pairStatesToRow(int s1, int s2,bool inverseOrder=false);
	static void columnToPairStates(int column,int &s1, int &s2, bool inverseOrder = false);


	pairOperators();
	~pairOperators();
};

