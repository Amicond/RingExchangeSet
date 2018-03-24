#pragma once
#include "LadderOperator.h"
class Term
{
	std::vector<LadderOperator> operators_;
public:
	bool operator ==(const Term right)const;
	bool operator<(const Term t2) const;

	std::string getName() const;
	
	bool parseTerm(std::string s, int max_length = -1);
	
	void substituteNodes(const std::vector<int> &NodeNums);
	
	int getTermLength();

	int getOperatorAmount();
	LadderOperator getLadderOperator(int num)const;
	
	bool chekIsZeroNode();
	
	void sortOperatorsName();
public:
	Term();
	~Term();
};

namespace std {
	template <>
	struct hash<Term>
	{
		std::size_t operator()(const Term& k) const
		{
			return (std::hash<std::string>()(k.getName()));
		}
	};
}

