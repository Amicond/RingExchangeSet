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
	if (operators.size() != right.operators.size())
		return false;
	for (int i = 0; i<operators.size(); i++)
		if (!(operators[i] == right.operators[i]))
			return false;
	return true;
}

bool Term::operator<(const Term t2) const
{
	if (operators.size() < t2.operators.size())
		return true;
	else if (operators.size() > t2.operators.size())
		return false;
	for (int i = 0; i < operators.size(); i++)
	{
		if (operators[i] < t2.operators[i])
			return true;
		else if (operators[i] < t2.operators[i])
			return false;
	}
	return false;
}

std::string Term::getName() const
{
	std::string name = "";
	for (auto &elem : operators)
	{
		name += elem.getName();
	}
	return name;
}

bool Term::parseTerm(std::string inpName, int max_length)
{
	operators.clear();
	LadderOperator curOp;
	//////////////////////////////////////////////////////////////////
	std::string opName;
	while (inpName.length() >= LadderOperator::getStrLength())
	{
		opName = inpName.substr(0, LadderOperator::getStrLength()-1);

		if (std::find(LadderOperator::OpNames.begin(), LadderOperator::OpNames.end(), opName) != LadderOperator::OpNames.end())
		{
			inpName = inpName.substr(LadderOperator::getStrLength()-1);
			int i = 0;
			for (; i < inpName.length(); i++)
			{
				if (!(inpName[i] <= '9'&&inpName[i] >= '0'))
					break;
			}
			if (i > 0)
			{
				curOp.parse(opName+inpName.substr(0, i));
				operators.push_back(curOp);
			}
			inpName = inpName.substr(i);
		}
		else
			break;
	}

	//////////////////////////////////////////////////////////////////
	if (max_length == -1 || getTermLength() <= max_length)
		return true;
	else
	{
		operators.clear();
		return false;
	}	
}

void Term::substituteNodes(const std::vector<int> &NodeNums)
{
	for (auto &elem : operators)
	{
		elem.setNode(NodeNums[elem.getNode()]);
	}
}

int Term::getTermLength()
{
	int length = 0;
	for (auto &elem : operators)
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
	return operators.size();
}
LadderOperator Term::getLadderOperator(int num)const
{
	if (num >= 0 && num < operators.size())
		return operators[num];
	else
		return LadderOperator();
}

bool Term::chekIsZeroNode()
{
	for (auto &elem : operators)
		if (elem.getNode() == 0)
			return true;
	return false;
}
