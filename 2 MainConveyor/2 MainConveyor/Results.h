#ifndef __RESULTS_H__
#define __RESULTS_H__


#include "globalConsts.h"
#include "Consts.h"
#include "waveFunction.h"
class Results
{
	double factors[ResAmount]; //итоговые множители при полном сворачивании
public:

	double getFactor(int num)const;
	void setFactor(int num, double value);
	void addToFactor(int num, double value);

	void clearForCurrentOrder(int order);
	Results& operator+=(const Results& tmp);

	void minus();

	void scalarProduct(WaveFunction& wf1, WaveFunction& wf2);
	void print(std::ostream &out);
	Results();
	~Results();
};
#endif // !__RESULTS_H__
