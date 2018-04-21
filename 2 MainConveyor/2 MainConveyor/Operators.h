#ifndef __OPERTATORS_H__
#define __OPERTATORS_H__


#include "stdafx.h"
#include "Consts.h"
#include "fileNamePrinter.h"

class Operators
{
	double vMatrix[SpinsInPlaquet][OrtsAmount][DiffStates][DiffStates];
	double vMatrixInside[DiffStates][DiffStates];//Operator that act only on one plaquett
	double Energie[DiffStates]; //Energie of plaquett's eigenstates
	static const std::string matrixNamePrefixes[];
	
	//Short form of Vmatrix
	std::vector<std::pair<int, double>> vMatrixNonZero[SpinsInPlaquet][OrtsAmount][DiffStates];
	std::vector<std::pair<int, double>> vMatrixInsideNonZero[DiffStates];
public:
	void readMatrixAndEnergie();
	void readPairMatrixAndEnergie();
	double getE0(int node_num);

	double getMatrixElements(int spinNumber, int ort, int inState, int outState)const;
	double getInsideMatrixElements(int inState, int outState)const;
	const double* getEnergiesOfStates()const;
	const std::vector<std::pair<int, double>>& getNonZeroElements(int spinNumber, int ort, int inState)const;
	const std::vector<std::pair<int, double>>& getNonZeroElementsInsideOperator(int inState)const;

	Operators();
	~Operators();
	
};
#endif // !__OPERTATORS_H__

