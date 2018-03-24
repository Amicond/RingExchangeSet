#pragma once
#include <string>
#include <vector>
class SOperator
{
	int nodeNum_;
	char type_;
public:
	static const int OpLength;
	static const std::vector<std::string> OpNames;
	static const std::vector<int> DoubleOpTermNames; //numbers of cells with double operators like bN*=bp*bk*	
	

	bool operator<(const LadderOperator right)const;
	bool operator==(const LadderOperator right)const;
	

	std::string getName() const;
	void parse(std::string s);
	
	char getType() const;
	int getNode() const;
	void setNode(int N);
	static int getStrLength();
	
public:
	LadderOperator();
	~LadderOperator();
};

