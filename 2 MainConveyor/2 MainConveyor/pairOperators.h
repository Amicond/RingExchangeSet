#pragma once
#ifndef PAIROPERATORS_H
#define PAIROPERATORS_H

#include "Consts.h"
#include "fileNamePrinter.h"
class pairOperators
{
public:
	static const std::string pairMatrixNames[]; //array of names of operators that act on two plaquet simultaneously
	//include J2-diag-UR, J2-diag-UL, J1-hor, J2-hor, J1-vert, J2-vert
	static const int pairMatrixAmount = 6;//must be consistent with previous array

	double Energie[DiffStates]; //Energie of plaquett's eigenstates

	
	void readMatrixAndEnergie();

	//double opMatrix[pairMatrixAmount][PairStates][PairStates];
	//temp version
	double ***opMatrix;
	double opMatrixInside[DiffStates][DiffStates];

	const double* getEnergiesOfStates()const;
	double getE0(int node_num);

	std::vector<std::pair<int, double>> opMatrixNonZero[pairMatrixAmount][PairStates];
	std::vector<std::pair<int, double>> opMatrixInsideNonZero[DiffStates];

	
	static int pairStatesToRow(int s1, int s2,bool inverseOrder=false);
	static void columnToPairStates(int column,int &s1, int &s2, bool inverseOrder = false);


	pairOperators();
	~pairOperators();
};

#endif //PAIROPERATORS_H
