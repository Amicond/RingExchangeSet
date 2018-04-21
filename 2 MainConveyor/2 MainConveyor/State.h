#ifndef __STATE_H__
#define __STATE_H__


#include "stdafx.h"
#include "JFactors.h"

class State
{
	double factor; //числовой множитель
	char coeff[JFactors::Npowers];  //coefficient powers. Names defined in "JFactors.cpp"
	std::vector<char> states;// номера состояний из соответствующих плакетов

public:
	
	bool operator<(const State &s) const;//только для 2ух состояний, переделать в высших порядках

	bool operator==(const State &s) const; //состояния равны если номера всех состояний равны

	bool check(const State &s);

	char getPowerByNumber(unsigned int num) const;

	char getStateByNumber(unsigned int num) const;

	double getFactor() const;

	double getEnergie(const double energies[]) const;
		
	void copyPowers(const State &s);

	void copyStates(const State &s);

	void incPower(unsigned int num);

	void setStateByNumber(unsigned int num, char newState);

	void setFactor(double initFactor);

	void multiplicateFactor(double multiplier);

	void addToFactor(double addition);

	void clear();

	void print(std::ostream &out);

	void addClusterState(int newStateNum);

	int getNodesNumber()const;

	State();
	State(unsigned int num);

	~State();
};

#endif // !__STATE_H__

