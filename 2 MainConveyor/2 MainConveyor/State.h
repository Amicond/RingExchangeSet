#pragma once
#include "stdafx.h"
#include "JFactors.h"

class State
{
	double factor; //числовой множитель
	char coeff[JFactors::Npowers];  //степени коэффициентов J1,J2 и (J2-J1)
	std::vector<char> states;// номера состо€ний из соответствующих плакетов

public:
	
	bool operator<(const State &s) const;//только дл€ 2ух состо€ний, переделать в высших пор€дках

	bool operator==(const State &s) const; //состо€ни€ равны если номера всех состо€ний равны

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

	void addClusterState(int newStateNum);

	int getNodesNumber()const;

	State();
	State(unsigned int num);

	~State();
};

