#pragma once
#include "stdafx.h"
#include "Consts.h"
#include "State.h"



State::State(unsigned int num)
{
	for (unsigned int i = 0; i < num; i++)
		states.push_back(DiffStates); //DiffStates - первое число, которое больше чем любой реальный номер состояния
	factor = 1;
	for (int i = 0; i < JFactors::Npowers; i++)
		coeff[i] = 0;
}
State::State() : State::State(0) {};

State::~State()
{
}

bool State::check(const State &s)
{
	bool Res = true;
	for (int i = 0; i<states.size(); i++)
		if (states[i] != s.states[i])
		{
			Res = false;
			break;
		}
	if (Res)
	{
		for (int i = 0; i<JFactors::Npowers; i++)
			if (s.coeff[i] != coeff[i])
			{
				Res = false;
				break;
			}
	}
	return Res;
}

bool State::operator==(const State &s) const //состояния равны если номера всех состояний равны
{
	if (states.size() != s.states.size()) return false;
	for (int i = 0; i<states.size(); i++)
		if (states[i] != s.states[i])
		{
			return false;
		}
	return true;
}

bool State::operator<(const State &s) const//только для 2ух состояний, переделать в высших порядках
{
	int i = 0;
	while (i<states.size())
	{
		if (states[i]<s.states[i]) return true;
		else if (states[i]>s.states[i]) return false;
		i++;
	}
	i = 0;
	while (i<JFactors::Npowers)
	{
		if (coeff[i]<s.coeff[i]) return true;
		else if (coeff[i]>s.coeff[i]) return false;
		i++;
	}
	return false;
}

char State::getPowerByNumber(unsigned int num) const
{
	return coeff[num];
}

char State::getStateByNumber(unsigned int num) const
{
	if (num < states.size())
		return states[num];
	else
		return DiffStates; //DiffStates - первое число, которое больше чем любой реальный номер состояния
}

double State::getFactor() const
{
	return factor;
}

double State::getEnergie(const double energies[]) const
{
	double res = 0;
	for (auto stateNum : states)
		res += energies[stateNum];
	return res;
}

void State::copyPowers(const State &s)
{
	for (int i = 0; i < JFactors::Npowers; i++)
	{
		coeff[i] = s.coeff[i];
	}
}

void State::copyStates(const State &s)
{
	states.clear();
	for (auto cur_n : s.states)
		states.push_back(cur_n);
}

void State::incPower(unsigned int num)
{
	if(num<JFactors::Npowers)
		coeff[num]++;
}

void State::setStateByNumber(unsigned int num, char newState)
{
	if (num < states.size() && newState < DiffStates)
	{
		states[num] = newState;
	}
}

void State::setFactor(double initFactor)
{
	factor = initFactor;
}

void State::multiplicateFactor(double multiplier)
{
	factor *= multiplier;
}

void State::addToFactor(double addition)
{
	factor += addition;
}

void State::clear()
{
	for (int i = 0; i < JFactors::Npowers; i++)
		coeff[i] = 0;
	states.clear();
}

void State::print(std::ostream &out)
{
	int powers[JFactors::Npowers];//for char to int conversion
	for (auto &stateNum : states)
		out << (int)stateNum << " ";
	out << ": ";
	out << factor<<"*";
	bool first = true;
	for (int i = 0; i < JFactors::Npowers; i++)
	{
		if (coeff[i] != 0)
		{
			if (!first)
				out << "*";
			first = false;
			out << JFactors::coefficientNames[i] << (int)coeff[i];
		}
	}
}

void State::addClusterState(int newStateNum)
{
	states.push_back(newStateNum);
}

int State::getNodesNumber()const
{
	return states.size();
}

