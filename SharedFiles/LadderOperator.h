#pragma once
#include <string>
#include <vector>
class LadderOperator
{
	int plaqeutNumber_;
	int nodeNumber_;
	char type_;
public:
	static const int OpLength;
	static const int ConstType;
	static const std::vector<std::string> OpNames;
	//static const std::vector<int> DoubleOpTermNames; //numbers of cells with double operators like bN*=bp*bk*	
	

	bool operator<(const LadderOperator right)const;
	bool operator==(const LadderOperator right)const;
	

	std::string getName() const;
	void parse(std::string s);
	
	char getType() const;
	int getPlaquetNumber() const;//position of current plaquet in current route
	void setPlaquetNumber(int newPlaquetNumber);

	int getNodeNumber() const; //number (according to Matrix with node numbers) of the node corresponding to current plaquet
	void setNodeNumber(int newNodeNumber);
	static int getStrLength();
	
public:
	LadderOperator();
	~LadderOperator();
};

