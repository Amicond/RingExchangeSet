#include "stdafx.h"
#include "LadderOperator.h"


//all names must have the same length!!!
const std::vector<std::string> LadderOperator::OpNames({ "am","ap","aN","bm","bp","bN","cm","cp","cN","dm","dp","dN" });
const std::vector<int> LadderOperator::DoubleOpTermNames({ 2,5,8,11 });//numbers of cells with double operators
const int LadderOperator::OpLength = 3;//length of string=OpName[i]+(1 char for node number)



LadderOperator::LadderOperator()
{
}


LadderOperator::~LadderOperator()
{
}

bool LadderOperator::operator<(const LadderOperator right)const
{
	if (nodeNum_<right.nodeNum_)
	{
		return true;
	}
	else
		if (right.nodeNum_<nodeNum_)
		{
			return false;
		}
		else
		{
			if (right.type_>type_)
				return true;
			else
				return false;
		}
}

bool LadderOperator::operator==(const LadderOperator right)const
{
	if ((nodeNum_ == right.nodeNum_) && (type_ == right.type_))
	{
		return true;
	}
	else
		return false;
}

std::string LadderOperator::getName() const
{
	std::string num = "";

	return OpNames[type_] + num;
}

void LadderOperator::parse(std::string s)
{
	std::string name = s.substr(0, OpNames[0].length());
	auto it = find(OpNames.begin(), OpNames.end(), name);
	if (it != OpNames.end())
	{
		type_ = distance(OpNames.begin(), it);
	}
	else
	{
		type_ = -1;
	}

	nodeNum_ = std::stoi(s.substr(OpNames[0].length(), 1));

}

int LadderOperator::getNode() const
{
	return nodeNum_;
}
void LadderOperator::setNode(int N)
{
	nodeNum_ = N;
}
char LadderOperator::getType() const
{
	return type_;
}

int LadderOperator::getStrLength()
{
	return OpLength;
}