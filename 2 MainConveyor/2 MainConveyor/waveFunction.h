#pragma once
#include "stdafx.h"
#include "Consts.h"
#include "State.h"
#include "Operators.h"

class WaveFunction
{
	std::vector<State> eigenStates;
	int nodesAmount;
	bool sorted;
	int Jpower[JFactors::Npowers];

public:
	void collect(WaveFunction &wf);
	void collect(std::vector<State> &wf);
	void sortWF();
	bool ifSorted()const;

	void setNodesAmount(int nodesAmount);
	int getNodesAmount()const;
	unsigned int getEigenstatesAmount()const;
	const State& WaveFunction::getEigenstateByNumber(int stateNumber)const;
	void addEigenState(State newEigenstate);
	void copyJPowers(const WaveFunction &wf);
	void incJPower(int num);
	int getJPower(int num) const;

	int findLastGroup(int startNumber);
	void clear(int nodeNumVal);
	WaveFunction();
	~WaveFunction();
};

