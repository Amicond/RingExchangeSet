#include "stdafx.h"
#include "LadderOperator.h"


//all names must have the same length!!!

const std::vector<std::string> LadderOperator::OpNames({"C","p","m","z"});//zero term reserved for constant term  //{ "am","ap","aN","bm","bp","bN","cm","cp","cN","dm","dp","dN" });
const int LadderOperator::ConstType = 0;
//const std::vector<int> LadderOperator::DoubleOpTermNames({ 2,5,8,11 });//numbers of cells with double operators
const int LadderOperator::OpLength = 2;//length of string=OpName[i]+(1 char for node number)




LadderOperator::LadderOperator()
{// initialization without any 
	type_ = -10;
	plaqeutNumber_ = -10;
	nodeNumber_ = -10;
}


LadderOperator::~LadderOperator()
{
}

bool LadderOperator::operator<(const LadderOperator right)const
{
	/*if (plaqeutNumber_<right.plaqeutNumber_)
		return true;
	else
		if (plaqeutNumber_>right.plaqeutNumber_)
			return false;
		else*/
		
	if (nodeNumber_ < right.nodeNumber_)
		return true;
	else
		if (nodeNumber_ > right.nodeNumber_)
			return false;
		else
			if (type_ < right.type_)
				return true;
			else
				return false;

}

bool LadderOperator::operator==(const LadderOperator right)const
{
	if ( (type_ == right.type_) && (nodeNumber_ == right.nodeNumber_))//&&(plaqeutNumber_ == right.plaqeutNumber_) 
	{
		return true;
	}
	else
		return false;
}

std::string LadderOperator::getName() const
{
	std::string num = "";
	if (type_ != ConstType)
		num=std::to_string(nodeNumber_);
	
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
	if (type_ == 0)
		plaqeutNumber_ = -1; //special case for const operator
	else
		plaqeutNumber_ = std::stoi(s.substr(OpNames[0].length(), 1));


}

int LadderOperator::getPlaquetNumber() const
{
	return plaqeutNumber_;
}
void LadderOperator::setPlaquetNumber(int newPlaquetNumber)
{
	if(type_!= ConstType)
		plaqeutNumber_ = newPlaquetNumber;
}

int LadderOperator::getNodeNumber() const
{
	return nodeNumber_;
}
void LadderOperator::setNodeNumber(int newNodeNumber)
{
	if (type_ != ConstType)
		nodeNumber_ = newNodeNumber;
}

char LadderOperator::getType() const
{
	return type_;
}

int LadderOperator::getStrLength()
{
	return OpLength;
}