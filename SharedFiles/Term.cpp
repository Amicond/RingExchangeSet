#pragma once
#include "stdafx.h"
#include <string>
#include <fstream>
#include "Term.h"

Term::Term()
{
}


Term::~Term()
{
}

bool Term::operator ==(const Term right)const
{
	if (operators_.size() != right.operators_.size())
		return false;
	for (int i = 0; i<operators_.size(); i++)
		if (!(operators_[i] == right.operators_[i]))
			return false;
	return true;
}

bool Term::operator<(const Term t2) const
{
	if (operators_.size() < t2.operators_.size())
		return true;
	else if (operators_.size() > t2.operators_.size())
		return false;
	for (int i = 0; i < operators_.size(); i++)
	{
		if (operators_[i] < t2.operators_[i])
			return true;
		else if (operators_[i] < t2.operators_[i])
			return false;
	}
	return false;
}

std::string Term::getName() const
{
	std::string name = "";
	for (auto &elem : operators_)
	{
		name += elem.getName();
	}
	return name;
}

bool Term::parseTerm(std::string inpName, int max_length)
{
	operators_.clear();
	LadderOperator curOp;
	//////////////////////////////////////////////////////////////////
	std::string opName;
	
	//extraCase for constant term
	if (inpName == LadderOperator::OpNames[LadderOperator::ConstType])
	{
		curOp.parse(inpName);
		operators_.push_back(curOp);
	}
	else//all other operators
	{
		while (inpName.length() >= LadderOperator::getStrLength())
		{
			opName = inpName.substr(0, LadderOperator::getStrLength() - 1);

			if (std::find(LadderOperator::OpNames.begin(), LadderOperator::OpNames.end(), opName) != LadderOperator::OpNames.end())
			{
				inpName = inpName.substr(LadderOperator::getStrLength() - 1);
				int i = 0;
				for (; i < inpName.length(); i++)
				{
					if (!(inpName[i] <= '9'&&inpName[i] >= '0'))
						break;
				}
				if (i > 0)
				{
					curOp.parse(opName + inpName.substr(0, i));
					operators_.push_back(curOp);
				}
				inpName = inpName.substr(i);
			}
			else
				break;
		}
	}

	//////////////////////////////////////////////////////////////////
	if (max_length == -1 || getTermLength() <= max_length)
		return true;
	else
	{
		operators_.clear();
		return false;
	}	
}

void Term::substituteNodes(const std::vector<int> &NodeNums)
{
	if (operators_.size()>0&& operators_[0].getType() != LadderOperator::ConstType) //substitute only in non-constant case
		for (auto &elem : operators_)
		{
				elem.setNodeNumber(NodeNums[elem.getPlaquetNumber()]);
		}
}

int Term::getTermLength()
{
	int length = 0;
	for (auto &elem : operators_)
	{
		if (elem.getName().find("N") != std::string::npos)
			length += 2;
		else
			length += 1;
	}
	return length;
}


int Term::getOperatorAmount()
{
	return operators_.size();
}
LadderOperator Term::getLadderOperator(int num)const
{
	if (num >= 0 && num < operators_.size())
		return operators_[num];
	else
		return LadderOperator();
}

bool Term::chekIsZeroNode()
{
	if (operators_.size() > 0 && operators_[0].getType() == LadderOperator::ConstType)
		return true;
	for (auto &elem : operators_)
		if (elem.getNodeNumber() == 0)
			return true;
	return false;
}

void Term::sortOperatorsName()
{
	std::sort(operators_.begin(), operators_.end());
}
