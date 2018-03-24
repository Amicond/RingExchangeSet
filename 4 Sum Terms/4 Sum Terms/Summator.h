#pragma once
#include "stdafx.h"
#include "globalConsts.h"
#include "Term.h"

class Summator
{
	std::unordered_map<Term, double> results_;
	std::vector<int> curRouteNodes_;
	int nodesInRoute_;
	int curRouteNumber_;
	int curTermLength_;
	static const double Treshold_;
	static const int AllLengthes_;

	
public:

	//debug
	static std::ofstream out_;
	//end debug

	Summator(int _curTermLength = AllLengthes_);
	
	void parseNewRoute(std::string inp);
	void parseNewRoute(int nodesNum);

	void parseNodes(std::string inp, bool isUncut = false);
	
	void addTerm(std::string inp, bool fullSummation);
	
	void print(std::ofstream &out);
	
	void clear();
	
};

