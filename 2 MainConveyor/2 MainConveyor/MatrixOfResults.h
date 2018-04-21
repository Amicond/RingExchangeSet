#ifndef __MATRIX_OF_RESULTS_H__
#define __MATRIX_OF_RESULTS_H__
#include "stdafx.h"
#include "JFactors.h"
#include "MyFunctions.h"



class MatrixOfResults
{

private:

	std::vector<std::vector<Results>> matrix;

public:

	MatrixOfResults(int s = 0);

	void clearAndSetSize(int s);

	bool add(int x, int y, const Results &curTerm);

	void printMatrix(std::string fname, int Order);
};
#endif __MATRIX_OF_RESULTS_H__