#pragma once

#include "Consts.h"
#include "fileNamePrinter.h"
class pairOperators
{
public:
	double opMatrix[AmountOfPairMatrixes][DiffStates*DiffStates][DiffStates*DiffStates];
	double Energie[DiffStates*DiffStates]; //Energie of plaquett's eigenstates
	
	static int statesToRow(int s1, int s2,bool inverseOrder=false);
	static void ColumnToStates(int column,int &s1, int &s2, bool inverseOrder = false);


	pairOperators();
	~pairOperators();
};

