
#ifndef PAIROPERATORS_H
#define PAIROPERATORS_H

#include "Consts.h"
#include "fileNamePrinter.h"
class pairOperators
{
public:
	static const std::string pairMatrixNames[]; //array of names of operators that act on two plaquet simultaneously
	
	static const int pairMatrixAmount = 8;//must be consistent with previous array

	double Energie[DiffStates]; //Energie of plaquett's eigenstates

	
	void readMatrixAndEnergie();

	//double opMatrix[pairMatrixAmount][PairStates][PairStates];
	//temp version
	double ***opMatrix;
	double opMatrixJInside[DiffStates][DiffStates];
	double opMatrixQInside[DiffStates][DiffStates];

	const double* getEnergiesOfStates()const;
	double getE0(int node_num);

	std::vector<std::pair<int, double>> opMatrixNonZero[pairMatrixAmount][PairStates];
	std::vector<std::pair<int, double>> opMatrixJInsideNonZero[DiffStates];
	std::vector<std::pair<int, double>> opMatrixQInsideNonZero[DiffStates];

	
	static int pairStatesToRow(int s1, int s2,bool inverseOrder=false);
	static void columnToPairStates(int column,int &s1, int &s2, bool inverseOrder = false);


	//getters
	//const std::vector<std::pair<int, double>>& getNonZeroElements(int spinNumber, int ort, int inState)const;
	//const std::vector<std::pair<int, double>>& getNonZeroElementsJInsideOperator(int inState)const;
	//const std::vector<std::pair<int, double>>& getNonZeroElementsQInsideOperator(int inState)const;

	pairOperators();
	~pairOperators();
};

#endif //PAIROPERATORS_H
