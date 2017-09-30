#pragma once
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